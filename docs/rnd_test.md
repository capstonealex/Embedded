# Procedure for Testing Trajectories on BBB

1. The files you require for testing are stored in the `RnD_Trajectory_Test` branch of Embedded Github, under [RnD Test Folder](https://github.com/capstonealex/Embedded/tree/RnD_Trajectory_Test/RnD%20Test). The files you need are `InitHardware.sh`, `homeCalibration.sh`, `CANfeast_Trajectory.c`. Clone this branch to your PC.
2. Use the BBB with number 1 writter on the ethernet port for your tests. 
3. Connect BBB to your PC using micro USB cable. 
4. Connect BBB to the X2 by connecting the ethernet cable as shown in table below.

      | Ethernet Cable Wire | CAN                    |
      | ------------------- |:----------------------:|
      | Green               | CAN-L                  |
      | White with Green    | CAN-H                  |
      | White with Orange   | Signal Ground          |

5. Connect to the BBB using Putty. Hostname: `debian@192.168.7.2` and password is `temppwd`. If a security authentication windows pops up, click yes. Putty is used to run remote terminal on the BBB. 
6. Connect to the BBB using WinSCP with same password and username as above. WinSCP is used to copy file from your PC to the BBB. 
7. Using WinSCP, copy the 3 files from Github onto the BBB. Copy these to any working folder you require.
6. Power on the X2 with both hips and knees fully flexed backwards. Keep holding the joints back for a few seconds before releasing. This sets the zero at the back joint limits. 
7. Got the Putty terminal, change to your working directory.
8. Run `sudo chmod a+x <filename>`. Password is `temppwd`. Do this for the 2 script files (.sh). (EOL error explanation.). Only needed for 1st time when downloaded from github.
9. Run `./InitHardware.sh`. From home folder. Restart BBB this script has issues. Let this run in the background. 
10. Open another terminal on Putty and connect to the BBB.
11. Raise the X2 fully off the ground and run `./homeCalibration.sh`. The joints will move to home position, which is fully straight. 
12. At this point, the system is read to go. Programs can now be run on it. CANfeast_tra has a frame work for testing. It contains an array with positions. Modify with new trajectories. Copy this file onto the working folder. Program logic and buttons. Proram initialise with seated or sitting. sitting is largest array index. 
13. Compile it on the BBB by running `gcc <filename> -Wall`. Look for warnings. Execuable is named a.out.
14. Run program with `./a.out`

## Shutdown


Switch off BBB with small black button near the ethernet port.

Link calibration and homing page. 

Mac ip 192.168.6.2. Keygen yes. If mismatch, run keygen -R