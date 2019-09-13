# CANopen
CANopen is a higher level protocol that sits on top of CANbus. This protocol gives us the features required for automation and robotics tasks. This page explains setting up CANopen comms using CANsocketOpen library. It also shows some basic SDO messaging.

## Sending CANopen messages to Accelnet Drive
1. Git clone the [canopensocket](https://github.com/CANopenNode/CANopenSocket) from github. Use below commands if you have git installed, else download manually.

      ```
      git clone https://github.com/CANopenNode/CANopenSocket.git
      cd CANopenSocket
      git submodule init
      git submodule update
      ```
   
      Note: If downloading manually, the canopennode subfolder has to be separately downloaded as this is a separate repository. 

3. Connect the BBB to the [CANbus network](https://embeded.readthedocs.io/en/latest/canopenHardware/#x2-canbus-cable-mapping) of the X2 and setup CAN1 interface on the BBB as stated in [CANbus section](https://embeded.readthedocs.io/en/latest/canbus/). Make sure to use the same bitrate the drives as configured in. Default is 1000000. You can verify this using the CME software.

3. Follow instructions in README.md on the github page for CANopenSocket. Below is an abridged version of the same.

5.	Open 3 terminals on BBB. On first terminal: `candump can1`

6.	2nd terminal: Navigate to canopend folder.  
      ```
      cd CANopenSocket/canopend
      make
      app/canopend -help
      app/canopend can1 -i 100 -c ""
      ```

      The 100 in the above line is the master node ID. Do not use zero or one of the existing [node IDs](https://embeded.readthedocs.io/en/latest/canopenHardware/#x2-canopen-node-id).
       
       Note: the "make" step is only required for 1st run.

8.	3rd terminal: navigate to canopencomm folder
   
      ```
      cd CANopenSocket/canopencomm
      make
      ./canopencomm –help
      ```
      
      Note: the "make" step is only required for 1st run.

9. Following can be used to set the heartbeat 1 every 5000ms for node ID 4 (Right Knee): `./canopencomm [1] 4 write 0x1017 0 i16 5000`


10. For changing states of node ID 4 use the following.  
      ```
      ./canopencomm 4 preop
      ./canopencomm 4 start
      ./canopencomm 4 stop
      ```
      
      Above can be used to change drive states.

## Example: Issuing Position Command on CANopen

The X2 node IDs can be found [here](https://embeded.readthedocs.io/en/latest/canopenHardware/#x2-canopen-node-id).

4. Setup CANopenSocket as shown above and make sure you can send canopencomm messages. See next steps for issuing relative position command to left knee motor. 
10. Set drive (node 2 here is left knee) to start mode: `./canopencomm 2 start` 
11. Read current position: `./canopencomm [1] 2 read 0x6063 0 i32`. The knee goes approximately 0 (fully extended) to 284,000 (fully bent). This assumes that system was powered on with knee fully extended. The drives set startup position as zero. 
12. Set drive to position mode: `./canopencomm [1] 2 write 0x6060 0 i8 1`. You can check current mode using: `./canopencomm [1] 2 read 0x6061 0 i8`. On startup, mode is 0 (nothing).
13. Set target position: `./canopencomm [1] 2 write 0x607A 0 i32 100000`. This is approximately half bent knee if you start from fully extended position. Note that this example uses relative motion. Also verify position by moving knee manually and reading position. 
14. Read status word: `./canopencomm [1] 2 read 0x6041 0 i16`. Should be 1591 (might be different based on actual drive state) if ready for motion. Convert 1591 to binary and compare to the bits in the Copley CANopen programmers manual for 0x6041 to get more details. 
15. Control word (0x6040) can now be used for motion. We need to change bit 4 from low to high to start motion. The entire control word goes from 0000000001101111 (decimal 111) to 0000000001111111 (decimal 127). So send, `./canopencomm [1] 2 write 0x6040 0 i16 111` followed by `./canopencomm [1] 2 write 0x6040 0 i16 127`. This should move the knee. See profile position mode for details on bits 4-6. For remaining bits, see control word in manual.

## Some Accelnet (Copley) CANopen Indices
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

## MISC
* To send negative values (say -1235) in canopencomm, use -- -1235. The -- specifies that the number is a value and not an option for the command.
* To add virtual nodes when using vcan, do the following step after step 5. On terminal 2: `cd CANopenSocket/canopend`. Then issue below command for each node after replace <NODE_ID> with correct ID. You can use ctrl + z and type `bg` to start another process for each of the node. 

      ```
      echo - > od<NODE_ID>_storage
      echo - > od<NODE_ID>_storage_auto
      app/canopend can1 -i <NODE_ID> -s od<NODE_ID>_storage -a od<NODE_ID>_storage_auto
      ```
