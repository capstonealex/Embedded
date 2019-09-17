# Procedure for Testing X2 Trajectories on BBB

You can follow the instructions on this page to test some simple position controlled motions. A more detailed version of this can be found in [RnD Trajectory Test](https://embeded.readthedocs.io/en/latest/rnd_test/).

## Startup Sequence
The scripts in the below instructions are stored in [Embedded/BBB Scripts/](https://github.com/capstonealex/Embedded/tree/master/BBB%20Scripts) and the simple program to standup, take 3 steps and sit down is stored in [Embedded/canOpenBeagle/canFeast/](https://github.com/capstonealex/Embedded/tree/master/canOpenBeagle/canFeast):`CanFeast_Walk.c`

1. Power on X2 with joints fully bent back. This is required for calibration.
2. Connect the BBB to the [CAN network](https://embeded.readthedocs.io/en/latest/canopenHardware/#x2-canbus-cable-mapping) of the X2. 
3. Power on BBB and connect it to your PC.
4. Setup [CANopenSocket](https://embeded.readthedocs.io/en/latest/Deployment/canopen_setup/).
4. SSH to BBB and run `./InitHardware.sh` on terminal 1. This sets up CANopen comms.
5. SSH another terminal to BBB and run `./homeCalibration.sh` on terminal 2. This calibrates the joints to a zero position.
6. Copy the required `CanFeast_Walk.c` program to working folder in BBB and compile using `gcc CanFeast_Walk.c -Wall -o sitwalk` from terminal 2.
7. Run the program using `.\sitwalk.out`

## Walk program instructions
* The program starts by displaying knee and hip positions. Pressing the green button locks position. The program assumes the X2 is in seated position, so only press green button when the X2 is roughly in seated position. 
* Now press blue button to stand up more. Press red button to sit down more. When fully standing, press green button to go to walk mode.
* Press red button to walk forward. Blue to walk backwards.
* Once all the steps are completed, press yellow button to go to sitting mode. 
* Press red button to sit more. Once fully seated, press yellow to release motors.