# CANopen
CANopen is a higher level protocol that sits on top of CANbus. This protocol gives us the features required for automation and robotics tasks. This page explains setting up CANopen comms using CANsocketOpen library. It also shows some basic SDO messaging.

## Sending CANopen messages on Accelnet Drive
1. Git clone the [canopensocket](https://github.com/CANopenNode/CANopenSocket) from github. Use below commands if you have git installed, else download manually.

      ```
      git clone https://github.com/CANopenNode/CANopenSocket.git
      cd CANopenSocket
      git submodule init
      git submodule update
      ```
   
      Note: If downloading manually, the canopennode subfolder has to be separately downloaded as this is a separate repository. 

3. Connect the BBB to the CANbus network and setup CAN1 interface on the BBB as stated in [CANbus section](https://embeded.readthedocs.io/en/latest/canbus/). Make sure to use the same bitrate the drives as configured in. Default is 1000000. You can verify this using the CME software.

3. Follow instructions in README.md on the github page for CANopenSocket. Below is an abridged version of the same.

5.	Open 3 terminals on BBB. On first terminal: `candump can1`

6.	2nd terminal: Navigate to canopend folder.  
      ```
      cd CANopenSocket/canopend
      make
      app/canopend -help
      app/canopend can1 -i 100 -c ""
      ```

      The 100
       in the above line is the master node ID. Using 0 here throws an error. For now, use a large unused ID.
       
       Note: the "make" step is only required for 1st run.

8.	3rd terminal: navigate to canopencomm folder
   
      ```
      cd CANopenSocket/canopencomm
      make
      ./canopencomm –help
      ```
      
      Note: the "make" step is only required for 1st run.

9. Following can be used to set the heartbeat 1 every 5000ms. The 1st 6 is the node ID: `./canopencomm [1] 6 write 0x1017 0 i16 5000`


10. For changing states use the following.  
      ```
      ./canopencomm 6 preop
      ./canopencomm 6 start
      ./canopencomm 6 stop
      ```
      
      Above can be used to change drive states.

## Connecting to the Exoskeleton and Issuing Position Command

Currently, an "ethernet" cable (accessible from outside) is connected to the exoskeleton CAN network. This serves as the CANbus interface for the BBB, i.e. it has CAN-H, CAN-L and GND. 

1. Connect this cable to the BBB CAN interface as shown in the table below.

      | Ethernet Cable Wire | CAN                    |
      | ------------------- |:----------------------:|
      | Green               | CAN-L                  |
      | White with Green    | CAN-H                  |
      | White with Orange   | Signal Ground          |

2. Setup BBB CAN1 from the embedded [wiki](https://embeded.readthedocs.io/en/latest/canbus/#configuring-the-bbb-can-interface). The exo CANbus is currently set to 1Mbps bitrate (1000000).
3. The X2 node IDs can be found [here](https://embeded.readthedocs.io/en/latest/canopenHardware/#x2-canopen-node-id).
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
* To send negative values (say -1235) in canopencomm, use -- -1235. The -- specifies that the number is a value and not an option for the command.
* To add virtual nodes when using vcan, do the following step after step 5. On terminal 2: `cd CANopenSocket/canopend`. Then issue below command for each node after replace <NODE_ID> with correct ID. You can use ctrl + z and type `bg` to start another process for each of the node. 

      ```
      echo - > od<NODE_ID>_storage
      echo - > od<NODE_ID>_storage_auto
      app/canopend can1 -i <NODE_ID> -s od<NODE_ID>_storage -a od<NODE_ID>_storage_auto
      ```
