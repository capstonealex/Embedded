**This section contains features that are currently in development and not fully tested/documented. They are recorded here for reference.**
# CANopen

## Sending CANopen messages on Accelnet Drive
1. Git clone the [canopensocket](https://github.com/CANopenNode/CANopenSocket) from github. 
   
      Note: The canopennode folder may have to be separately downloaded. Check canopennode folder and see if empty. Transfer the entire folder it over to BBB. 

2. Follow instructions in README.md on the github page for CANopenSocket. Below is an abridged version of the same.
3.	Setup BBB CAN1 from the embedded [wiki](https://embeded.readthedocs.io/en/latest/canbus/#configuring-the-bbb-can-interface). Make sure to use same bitrate in setup here and the CAN config in the [CME software](https://embeded.readthedocs.io/en/latest/canbus/#accelnet-serial-comms). 
4.	Connect to drive using serial. Reset the drive using CME to clear network errors. Also check bitrate and note the node ID.
5.	Open 3 terminals on BBB. On first terminal: `candump can1`

6.	2nd terminal: Navigate to canopend folder.  
      ```
      app/canopend can1 -i 100 -c ""
      ```

      The 100
       in the above line is the master node ID. Using 0 here throws an error. For now, use a large unused ID.

8.	3rd terminal: navigate to canopencomm folder
   
      ```
      cd CANopenSocket/canopencomm
      make
      ./canopencomm –help
      ```
      
      Note: the "make" step is only required once.

9. Following can be used to set the heartbeat 1 every 5000ms. The 1st 6 is the node ID: `./canopencomm [1] 6 write 0x1017 0 i16 5000`


10. For changing states use the following.  
      ```
      ./canopencomm 6 preop
      ./canopencomm 6 start
      ./canopencomm 6 stop
      ```
      
      Above can be used to change drive states.

## Connecting to the Exoskeleton and Issuing Position Command

Currently, an ethernet cable (accessible from outside) is connected to the exoskeleton network switch. This serves as the CANbus interface for the BBB, i.e. it has CAN-H, CAN-L and GND. Internally, the old MMU is disconnected. The rest of the wiring has to be verfied: termination resistance, sensors and motors.

1. Connect the ethernet cable to the BBB CAN interface as shown in the table below.

      | Ethernet Cable Wire | CAN                    |
      | ------------------- |:----------------------:|
      | Green               | CAN-L                  |
      | White with Green    | CAN-H                  |
      | White with Orange   | Signal Ground          |

2.	Setup BBB CAN1 from the embedded [wiki](https://embeded.readthedocs.io/en/latest/canbus/#configuring-the-bbb-can-interface). The exo CANbus is currently set to 1Mbps bitrate (1000000).
3. The following are the currently identified node ID:

      | Node ID             | Device                 |
      | ------------------- |:----------------------:|
      | 1                   | Left Hip Motor         |
      | 2                   | Left Knee Motor        |

4. On a BBB with CANopenSocket installed, open 3 terminals. 
5. On terminal 1: `candump can1`

8. In terminal 2, run following for the master: `cd CANopenSocket/canopend` followed by `app/canopend can1 -i 100 -c ""`. At this stage, you should be able to see the heartbeat in terminal 1 if it is setup.

9. On terminal 3: `cd CANopenSocket/canopencomm`. Now you can start issuing CANopen commands. See next steps for issuing relative position command to left knee motor. 

      | Function                  | Index                    | Manual Pg #|
      | ------------------------- |:------------------------:|:----------:|
      | Position Actual Value     | 0x6063                   | 133        |
      | Target Position           | 0x607A                   | 195        |
      | Mode of Position          | 0x6060                   | 65         |
      | Display Mode              | 0x6061                   | 65         |
      | Control Word              | 0x6040                   | 59         |
      | Status Word               | 0x6041                   | 60         |
      | Profile Position Mode Bits| bits 4,5,6 of 0x6040     | 191        |

      See [Copley CANopen Programmer's Manual](http://www.copleycontrols.com/wp-content/uploads/2018/02/All-CANopen_Programmers_Manual-Manual.pdf) for more details.

10. Set drive to start mode: `./canopencomm 2 start` 
11. Read current position: `./canopencomm [1] 2 read 0x6063 0 i32`. The knee goes approximately 0 (fully extended) to 260,000 (fully bent).
12. Set drive to position mode: `./canopencomm [1] 2 write 0x6060 0 i8 1`. You can check current mode using: `./canopencomm [1] 2 read 0x6061 0 i8`. On startup, mode is 0 (nothing).
13. Set target position: `./canopencomm [1] 2 write 0x607A 0 i32 100000`. This is approximately half bent knee if you start from fully extended position. Note that this example uses relative motion. Also verify position by moving knee manually and reading position. 
14. Read status word: `./canopencomm [1] 2 read 0x6041 0 i16`. Should be 1591 (to be verified) if ready for motion. Convert 1591 to binary and compare to the bits in the manual for 0x6041 to get more details. 
15. Control word (0x6040) can now be used for motion. We need to change bit 4 from low to high to start motion. The entire control word goes from 0000000001101111 (decimal 111) to 0000000001111111 (decimal 127). So send, `./canopencomm [1] 2 write 0x6040 0 i16 111` followed by `./canopencomm [1] 2 write 0x6040 0 i16 127`. This should move the knee. See profile position mode for details on bits 4-6. For remaining bits, see control word in manual.

## MISC
* The zero (home) position of the motor set to current position when exo skeleton is powered on. 
* To send negative values in canopencomm, use -- -number. The -- specifies that the number is a value and not an option for the command.
* To add virtual nodes when using vcan, do the following step after step 5. On terminal 2: `cd CANopenSocket/canopend`. Then issue below command for each node after replace <NODE_ID> with correct ID. You can use ctrl + z and type `bg` to start another process for each of the node. 

      ```
      echo - > od<NODE_ID>_storage
      echo - > od<NODE_ID>_storage_auto
      app/canopend can1 -i <NODE_ID> -s od<NODE_ID>_storage -a od<NODE_ID>_storage_auto
      ```

## Resources to look into
 - **Basics of CANopen**

    <https://www.ni.com/en-au/innovations/white-papers/13/the-basics-of-canopen.html>

    Probably need OD (object dictionary) for constructing messages for particular devices.
    
    
 - **Constructing Messages Manuallly**

    <http://robotsforroboticists.com/can-bus/>
    
    See bottom of page. Probably can use this for cansend on can-utils (linux)
    
 - **Video guide to CANopen**

    <https://www.youtube.com/watch?v=iIkBJ4NheCc>

 - **CAN-utils**
    
    <https://blog.mbedded.ninja/programming/operating-systems/linux/how-to-use-socketcan-with-the-command-line-in-linux/>

    cansend and candump quick guide.

 - **CMO for CANopen guide**
    
    <https://www.youtube.com/watch?v=NNlMBlTM228>
    
    <https://www.youtube.com/watch?v=i60Kk0K8KW8>

    CMO is used by copley for CANopen comms. Most of the 1st video is unusable since we are using a BBB for comms. But we maybe able to use the C++ code at the end to construct messages. 
    The 2nd video mentions that we can use the CMO library with other tools as well. Might be worth looking into.

 - **CANopenSocket**
   
    <https://github.com/CANopenNode/CANopenSocket>

    Linux tools for constructing/reading CANopen messages.

 - **CANfestival**
 
    <https://basdebruijn.com/2015/05/sniffing-at-canopen/>
    
    <https://canfestival.org/>

    Tools for CANopen.

- **CANopen using python**

    <https://buildmedia.readthedocs.org/media/pdf/canopen/latest/canopen.pdf>

    Python libraries for constructing CANopen messages.
