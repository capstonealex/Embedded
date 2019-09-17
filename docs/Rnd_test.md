# Procedure for Testing X2 Trajectories on BBB

For controlling the X2, you will need a Beagle Bone Black with a [comms cape](https://github.com/beagleboard/capes/tree/master/beaglebone/Comms). This cape enables CANbus connections without additional hardware. 

You can follow the instructions in this page to test some simple position controlled motions.

## Startup Sequence
This is summary of the startup procedure. Following this out of sequence may cause SDO timeouts. For more details on each step, read the sections below. 

1. Power on X2 with joints fully bent back.
2. Connect ethernet cable to BBB cape CAN pins. 
3. Power on BBB (connect USB cable to PC).
4. Run `./InitHardware.sh` on terminal 1.
5. Run `./homeCalibration.sh` on terminal 2.
6. Copy the required c program to working folder in BBB and compile using `gcc <filename>.c -Wall` in terminal 2.
7. Run program from terminal 2 using `./a.out`.
7. Control X2 using handheld buttons.

## Initial Setup
1. The files you require for testing are stored in the `RnD_Trajectory_Test` branch of Embedded Github, under [RnD Test Folder](https://github.com/capstonealex/Embedded/tree/RnD_Trajectory_Test/RnD%20Test). The files you need are `InitHardware.sh`, `homeCalibration.sh`, and `CanFeast_Trajectory.c`. Clone this branch to your PC.
2. Use the BBB with number 1 written on the ethernet port for your tests. 
3. Connect BBB to your PC using micro USB cable. 
4. Connect BBB to the X2 by connecting the ethernet cable as shown in table below.

      | Ethernet Cable Wire | CAN Pins on BBB        |
      | ------------------- |:----------------------:|
      | Green               | CAN-L                  |
      | White with Green    | CAN-H                  |
      | White with Orange   | Signal Ground          |

5. Connect to the BBB using Putty (for mac use ssh from terminal). Hostname: `debian@192.168.7.2` (for mac use 192.168.6.2) and password is `temppwd`. Putty is used to run remote terminal on the BBB. 

      * If a security authentication windows pops up, click yes. Note: If you get SSH authentication error, run `ssh-keygen -R 192.168.7.2` in terminal on your pc/mac. You may need to change to 192.168.6.2 on the mac.

6. Connect to the BBB using WinSCP with same password and username as above. WinSCP is used to copy files from your PC to the BBB. 
7. Using WinSCP, copy the 2 script files (.sh) from Github onto the BBB. Copy these to any working folder you require.

## Calibrating the X2
1. Power on the X2 with both hips and knees fully flexed backwards. Keep holding the joints back for a few seconds before releasing. This sets the zero at the back joint limits. 
2. Go the Putty terminal, change to your working directory using `cd <folder>`.
3. To run scripts, you need to enable execution permission (only for the 1st time when copied to BBB from github). Run `sudo chmod a+x <filename>`. Do this for the 2 script files (.sh extension).

      * If you get a bad interpreter error, this is due to End-of-Line character being different on Windos, Mac and Unix. Use a text editor like notepad++ to change this. On notepad++, this is `Edit > EOL Conversion > Unix (LF)`.

4. Run `./InitHardware.sh`. This starts the communication with the X2. No more instructions are issued on this terminal. But make sure that this process is running (i.e. the terminal prompt doesn't show.) and does not terminate. Check troubleshooting section below for fix if this socket fails/closes.  
5. Open another terminal on Putty and connect to the BBB.
6. Raise the X2 fully off the ground and run `./homeCalibration.sh`. The joints will move to home position, which is fully straight. 
      * The calibration step needs to be rerun if and only if the X2 is switched off.
      * If you get SDO timeout errors, run `sudo ifconfig can1 down`. This closes the CAN interface. Now try again from step 4 in this section.
7. At this point, the system is read to go. Programs can now be run on it. 

## Running Trajectories
`CanFeast_Trajectory.c` is the main program you use for testing trajectories. In the `sitStand()` function, there are 2 arrays: `sitStandArrHip_degrees[]` and `sitStandArrKnee_degrees[]` that store the trajectory of hip and knee in degree. These arrays are iterated through by a state machine in the sitStand() function. 

1. Start by modifying the `CanFeast_Trajectory.c` program trajectory array (mentioned above) with values you need. You can do this on your pc.
2. In the main function, change the argument of sitStand() with either `SITTING` or `STANDING` depending on whether the starting position of X2 is at end of array or start of array respectively.
3. Save and copy this file to the BBB using WinSCP.
2. Compile it on the BBB by running `gcc CanFeast_Trajectory.c -Wall` from a Putty terminal. Look for warnings. Execuable is named `a.out` by default.
3. Run program with `./a.out`.
4. When the program is running, it displays the current knee and joint angles. Pressing green button locks the motor in position. Try to lock it close to either the beginning/ending value in the array. To see relation between motor angle values and the degree values, see [this](https://embeded.readthedocs.io/en/latest/calibration/).
5. Red button sits down more. Blue button stands more. Yellow button stops program and disengages motor.

## Shutdown Procedure

1. If the program is running, end it by pressing yellow button.
2. Switch off the X2 using the green button on the back.
3. Switch off BBB with small black button near the ethernet port.
4. Disconnect the cables. 

## Logging Position and Torque
To log position and torque, the startup sequence has to be done with a few additional steps.

1. Power on X2 with joints fully bent back.
2. Connect ethernet cable to BBB cape CAN pins. 
3. Power on BBB (connect USB cable to PC).
4. Run `./InitHardware_PDO.sh` on terminal 1. Note that this is a different script,
5. Run `./homeCalibration.sh` on terminal 2.
6. Run `./RemapPDO2.sh`. This is an extra step. 
6. Copy the required c program to working folder in BBB and compile using `gcc <filename>.c -Wall` in terminal 2.
7. Run program from terminal 2 using `./a.out`.
7. Control X2 using handheld buttons.
8. Once done, close the sockets in terminal 1 using `ctrl+c`.

The log file name `X2_log.txt` can be obtained from `CANopenSocket/canopend/` folder. The data is stored in the format `time(seconds), time(microseconds), Left Hip Pos, Left Hip Torque, , Left Knee Pos, Left Knee Torque,, Right Hip Pos, Right Hip Torque,, Right Knee Pos, Right Knee Torque`. Torque is has unit `rated torque/1000`, i.e. a reading of 500 means that current torque is half of rated torque. The positions are shown as motor count values. See [calibration](https://embeded.readthedocs.io/en/latest/calibration/) page for details.


## Troubleshooting

### Tracking Error (Motor Getting Disabled)
If you exceed the motor torque on the joint, they may go to a tracking fault state. To fix this, first exit the program using button 3 (yellow). To unlatch this fault, run the `./resetTrackingError.sh`. This script is stored in the [RnD Test Folder](https://github.com/capstonealex/Embedded/tree/RnD_Trajectory_Test/RnD%20Test). 

### Socket failure recovery
If the `InitHardware` terminal script stops running. This means the socket between the main Robot application running canFeast failed, or some socket error occured. To fix this:

1. In a terminal type: `unlink /tmp/CO_command_socket`.
2. Run `./InitHardware.sh`.
3. Begin your application again.