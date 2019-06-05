## CANbus
The Fourier X2 exoskelton currently uses the Accelnet [ACJ-055-18](https://www.copleycontrols.com/en/products/acj-055-18) servo drives. These support the CANopen protocol. We use BeagleBoneBlack with a [comms cape](https://github.com/beagleboard/capes/tree/master/beaglebone/Comms) for communicating with it. BBB has 2 CAN controllers: DCAN0 and DCAN1. But the pins for DCAN0 are used by the comms cape. These capes already have a terminating resistance (120Ω) between CAN-H and CAN-L.

Note: CANbus is a physical/data link later protocol. CANOpen is a higher layer protocol.

## Configuring the BBB CAN interface
1. We will be using DCAN1 controller on BBB for CAN comms. For this pins P9_24 and P9_26 have to be configured correctly. You can check current config by running `config-pin -q P9.24`. If it is configured for CAN, it will shows "p9_24 Mode: can".
2. To config pins for CAN: `config-pin -q P9.24` and `config-pin -q P2.9`.
3. Load LKMs for CAN:

    ```
    dmesg|grep can
    sudo modprobe can
    sudo modprobe can-dev
    sudo modprobe can-raw
    lsmod|grep can
    mesg|grep raw
    ```

5. Setup the CAN link: `sudo ip link set can1 up type can bitrate 115200`. The 115200 can be replaced with your required bitrate. Then run `sudo ifconfig can1 up`.
6. You can run `ifconfig` to check that the CAN interface is running. You should see CAN as one of the adapters along with ethernet. 

## Testing CAN messages between BBB
BBB distro Debian 9 onwards comes preinstalled with can-utils. We can use this send and received messages over CAN bus. 
1. Wire up the BBBs as shown in the section [below](https://embeded.readthedocs.io/en/latest/canbus/#canbus-wiring-for-bbb-and-accelnet). Basically the connect CAN-H to CAN-H, CAN-L to CAN-L, and common grounds. Do note that the last device in the daisy chain should have a 120Ω terminating resistance between CAN-H and CAN-L. This is already included in the BBB Comms cape. 
2. Setup the DCAN1 controller on BBB for CAN using steps [above](https://embeded.readthedocs.io/en/latest/canbus/#configuring-the-bbb-can-interface).
3. On one of the BBB, send a can message using `cansend can1 123#fe.ed.be.ef`. On the other BBB, run `candump can1`. Note that the message and node ID used here are arbitrary since candump will read all messages being sent through the canbus.

## TRP-C08 USB-Serial Adapter Setup

## Accelnet Serial Comms

## CANbus wiring for BBB and Accelnet