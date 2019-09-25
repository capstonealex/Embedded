## CANbus

This section explains setting up a CANbus network between 2 BBB and sending CAN messages using linux CAN-Utils. This page is primarily for understanding CANbus comms and is not directly required for using the X2. Also, most of the commands stated here are included in the [BBB Scripts](https://github.com/capstonealex/Embedded/tree/master/BBB%20Scripts).

 We use BeagleBoneBlack with a [comms cape](https://github.com/beagleboard/capes/tree/master/beaglebone/Comms) for communicating on the CAN network. BBB has 2 CAN controllers: DCAN0 and DCAN1. But the pins for DCAN0 are used by the comms cape, so we will be using DCAN1 exclusively. Note that these capes already have a terminating resistance (120Ω) between CAN-H and CAN-L.

Note: CANbus is a physical/data link later protocol. CANOpen is a higher layer protocol.

## Configuring the BBB CAN interface
1. We will be using DCAN1 controller on BBB for CAN comms. For this pins P9_24 and P9_26 have to be configured correctly. You can check current config by running `config-pin -q P9.24`. If it is configured for CAN, it will shows "p9_24 Mode: can".
2. To config pins for CAN: `sudo config-pin p9.24 can` and `sudo config-pin p9.26 can`.
3. Load LKMs for CAN:

    ```
    dmesg|grep can
    sudo modprobe can
    sudo modprobe can-dev
    sudo modprobe can-raw
    lsmod|grep can
    mesg|grep raw
    ```

5. Setup the CAN link: `sudo ip link set can1 up type can bitrate 1000000`. The 1000000 can be replaced with your required bitrate. Then run `sudo ifconfig can1 up`. 
        
    Note: `sudo ifconfig can1 down` can be used to close the network interface. This is useful if you want to change parameters, like bitrate.

6. You can run `ifconfig` to check that the CAN interface is running. You should see CAN as one of the adapters along with ethernet. 

## Testing CAN messages between BBB
BBB distro Debian 9 onwards comes preinstalled with can-utils. We can use this send and received messages over CAN bus. 

1. Wire up the BBBs by connecting CAN-H to CAN-H, CAN-L to CAN-L, and common grounds. Do note that the last device in the daisy chain should have a 120Ω terminating resistance between CAN-H and CAN-L. This is already included in the BBB Comms cape. 
2. Setup the DCAN1 controller on BBB for CAN using steps [above](https://exoembedded.readthedocs.io/en/latest/canbus/#configuring-the-bbb-can-interface).
3. On one of the BBB, send a can message using `cansend can1 123#fe.ed.be.ef`. On the other BBB, run `candump can1`. Note that the message and node ID used here are arbitrary since candump will read all messages being sent through the canbus.