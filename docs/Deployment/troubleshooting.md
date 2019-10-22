## Tracking Error (Motor Getting Disabled)
If you exceed the motor torque on the joint, they may go to a tracking fault state. To fix this, firstly stop the program you are running. To unlatch this fault, run the `./resetTrackingError.sh`. This script is stored in the [BBB Script Folder](https://github.com/capstonealex/Embedded/tree/master/BBB%20Scripts). 

## Socket failure recovery
If the `InitHardware` terminal script stops running. This means the socket between the main Robot application running canFeast failed, or some socket error occurred. To fix this:

1. In a terminal type: `unlink /tmp/CO_command_socket`.
2. Run `./InitHardware.sh`.
3. Begin your application again.

## SDO Timeout
This potentially can happen if the components are connected up in the wrong order. Currently, the fix is to connect and startup system as below:

1. Start with everything turned off and disconnected.
2. Power on the X2 exoskeleton.
3. Connect the CAN cables from X2 to BBB.
4. Power on the BBB. 
5. Run the initialisation scripts: `./InitHardware.sh`.

The system should now be fixed.

## CAN Interface Reset

1. Run `sudo ifconfig can1 down`. This closes the CAN1 interface.