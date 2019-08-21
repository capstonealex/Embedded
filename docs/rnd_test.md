# Procedure for Testing Trajectories on BBB

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

4. Run `./InitHardware.sh`. This starts the communication with the X2. No more instructions are issued on this terminal. But make sure that this process is running (i.e. the terminal prompt doesn't show.) and does not terminate. Restart BBB and redo these steps if this process fails.  
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
