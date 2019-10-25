/*
 * Application interface for CANopenSocket.
 *
 * @file        application.c
 * @author      Janez Paternoster
 * @copyright   2016 Janez Paternoster
 *
 * This file is part of CANopenSocket, a Linux implementation of CANopen
 * stack with master functionality. Project home page is
 * <https://github.com/CANopenNode/CANopenSocket>. CANopenSocket is based
 * on CANopenNode: <https://github.com/CANopenNode/CANopenNode>.
 *
 * CANopenSocket is free and open source software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "CANopen.h"
#include "stdio.h"
#include <stdint.h>
#include <sys/time.h>

//header files for the implementing logging using spdlog techniques.
#include <iostream>
#include <string.h>
#include <sstream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

//// Data logger helper functions
void fileLoggerBinary();
void fileLogHeader();
void fileLogger();
void strreverse(char *begin, char *end);
void itoa(int value, char *str, int base);

/* File has been modified by Mihai Blaga to implement more robust
 * logging through the implementation of spdlog. */
auto* createLogger(std::string logID, std::string fileLocation);
void setLoggerStyle(auto* logger);
//Path to the file in which all of the log files are stored.
const std::string logFolder = "\logs\";

/******************************************************************************/
void app_programStart(void){
    //void fileLogHeader();
}
/******************************************************************************/
void app_communicationReset(void){
}
/******************************************************************************/
void app_programEnd(void){
}
/******************************************************************************/
void app_programAsync(uint16_t timer1msDiff){
//Timing speed of reading from memory and file writing
//struct timeval start;
//struct timeval stop;
//gettimeofday(&start, NULL);

//struct timeval tv;
//gettimeofday(&tv,NULL);
//printf("time before(s): %lu, (us): %lu\n",tv.tv_sec, tv.tv_usec);
//fileLogger(timer1msDiff);
//gettimeofday(&tv,NULL);
//printf("time after(s): %lu, (us): %lu\n",tv.tv_sec, tv.tv_usec);

//gettimeofday(&stop, NULL);
//double elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
//elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;
//printf("TASK 1:  %.2f milliseconds\n", elapsed_ms);
}

/******************************************************************************/
//creating a logger at a designated fileLocation.
auto* createLogger(std::string logID, std::string fileLocation){
	try{
	 	auto logger = spdlog::basic_logger_mt(logID, fileLocation);
		setLoggerStyle(logger);
		return logger;
	} catch (const spdlog::spdlog_ex& ex){
		std::cout << "Failed to create log: " << ex.what() << std::endl;
		return;
	}
}

//setting the style of the logger to only hold the data without any extra information.
void setLoggerStyle(auto* logger){
	logger->set_pattern("%v");	
}
/******************************************************************************/

/******************************************************************************/
//treated as main function.
void app_program1ms(void){
	mainLogger = createLogger("parent", logFolder + "X2_log.txt");
	spd::set_default_logger(mainLogger);
	
	fileLoggerBinary(mainLogger);
}
/******************************************************************************/
void itoa(int value, char *str, int base)
{
    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *wstr = str;
    int sign;
    // Validate base
    if (base < 2 || base > 35)
    {
        *wstr = '\0';
        return;
    }
    // Take care of sign
    if ((sign = value) < 0)
        value = -value;
    // Conversion. Number is reversed.
    do
        *wstr++ = num[value % base];
    while (value /= base);
    if (sign < 0)
        *wstr++ = '-';
    *wstr = '\0';
    // Reverse string
    strreverse(str, wstr - 1);
}
/******************************************************************************/
//can do this with std::reverse.
void strreverse(char *begin, char *end)
{
    char aux;
    while (end > begin)
        aux = *end, *end-- = *begin, *begin++ = aux;
}
/******************************************************************************/
void fileLogger(auto* logger){
    //printf("fileLogger beggining\n");
	
    // Generate whatever you want logged here, "data" is just an example
    	char position [50];
	char timestamp [50];
    	char torque[50];
    	char comma[] = ", ";
	
	//Getting timestamp
	//printf("time(s): %lu, (us): %lu\n",tv.tv_sec, tv.tv_usec);
    	//itoa(timer1msDiff, position, 10);
	struct timeval tv;
	gettimeofday(&tv,NULL);
	itoa(tv.tv_sec, timestamp, 10);
	
	mainLogger->info("{}, ", timestamp);
	
	itoa(tv.tv_usec, timestamp, 10);
	
	mainLogger->info("{}, ", timestamp);
	
	uint32_t motorpos[4];
	uint16_t motorTor[4];
	
	/* Motor 1: Left Hip
	 * Motor 2: Left Knee
	 * Motor 3: Right Hip
	 * Motor 4: Right Knee */
	
	motorpos[0] = CO_OD_RAM.actualMotorPositions.motor1;
	motorpos[1] = CO_OD_RAM.actualMotorPositions.motor2;
	motorpos[2] = CO_OD_RAM.actualMotorPositions.motor3;
	motorpos[3] = CO_OD_RAM.actualMotorPositions.motor4;
	
	motorTor[0] = CO_OD_RAM.statusWords.motor1;
	motorTor[1] = CO_OD_RAM.statusWords.motor2;
	motorTor[2] = CO_OD_RAM.statusWords.motor3;
	motorTor[3] = CO_OD_RAM.statusWords.motor4;
	
	std::stringstream output;
	
	for (int i = 0; i<4; i++){
		itoa(motorpos[i], position, 10);
		itoa(motorTor[i], torque, 10);
		
		output << position << ", " << torque << ", ";
	}
	
	output << "\n";
	
	logger->info(output.str());
	
}
void fileLogHeader(auto* logger){
   	mainLogger = createLogger("parent", logFolder + "X2_log.txt");
	spd::set_default_logger(mainLogger);
	
	std::stringstream header;
	
    	header << "======================================\n";
    	header << "X2 exoskeleton torque and position log\n";
    	header << "======================================\n";
    	header << "Time(s), time(ms) LHPos, LHT, LKPos, LKT, RHPos, RHT, RKPos, RKT\n";
    
	logger->info(header.str());
}

void fileLoggerBinary(){
    	parent = createLogger("parent", logFolder + "parent.txt");
	spd::set_default_logger(mainLogger);

    	struct timeval tv;
    	gettimeofday(&tv,NULL);

	uint32_t motorpos[4];
	uint16_t motorTor[4];
	
	motorpos[0] = CO_OD_RAM.actualMotorPositions.motor1;
	motorpos[1] = CO_OD_RAM.actualMotorPositions.motor2;
	motorpos[2] = CO_OD_RAM.actualMotorPositions.motor3;
	motorpos[3] = CO_OD_RAM.actualMotorPositions.motor4;
	
	motorTor[0] = CO_OD_RAM.statusWords.motor1;
	motorTor[1] = CO_OD_RAM.statusWords.motor2;
	motorTor[2] = CO_OD_RAM.statusWords.motor3;
	motorTor[3] = CO_OD_RAM.statusWords.motor4;
	
    	long long timesec=tv.tv_sec;
    	long timeusec=tv.tv_usec;
	
	std::stringstream content;

	content << timesec << timeusec;
	
	for(int i = 0; i<4; i++){
		content << motorpos[i] << motorTor[i];
	}
	
	parent->info(content.str());
}
