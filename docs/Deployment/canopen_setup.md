# CANopen Setup

This section explains setting up CANopen communication on a BBB with [comms cape](https://github.com/beagleboard/capes/tree/master/beaglebone/Comms). This cape enables CANbus connections without additional hardware. 

## Setting up CANopenSocket

1. Clone the [CANopenSocket](https://github.com/CANopenNode/CANopenSocket) repo and its submodules (CANopenNode).

    ```
    git clone https://github.com/CANopenNode/CANopenSocket.git
    cd CANopenSocket
    git submodule init
    git submodule update
    ```

2. Put CANopenSocket folder in the `/home/debian/` folder on BBB.
3. Compile CANopenSocket and canopencomm:

    ```
    cd CANopenSocket/canopend
    make
    ```

    and, go back to home folder `cd /`, then run

    ```
    cd CANopenSocket/canopencomm
    make
    ```

## Starting the communication
1. Firstly connect the BBB to the [CANbus network](https://exoembedded.readthedocs.io/en/latest/canopenHardware/#x2-canbus-cable-mapping) of the X2.
2. The communication setup requires CAN pins to be enabled on the BBB comms cape, and canopend (in CANopenSocket) has to be started. 
3. This can be done using the InitHardware.sh script from the [BBB Script Folder](https://github.com/capstonealex/Embedded/tree/master/BBB%20Scripts). Copy this file to BBB `/home/debian/` folder and run it: `./InitHardware.sh`.
4. The system is now setup to run programs that use CANopen.
