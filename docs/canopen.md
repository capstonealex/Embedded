**This section contains features that are currently in development and not fully tested/documented. They are recorded here for reference.**
# CANopen

## Sending CANopen messages
1. Git clone the [canopensocket](https://github.com/CANopenNode/CANopenSocket) from github. Note: The canopennode folder may have to be separately downloaded. Check canopennode folder and see if empty. Transfer the entire folder it over to BBB. 
2. Follow instructions in README.md on the github page for CANopenSocket. Below is an abridged version of the same.
1.	Setup BBB CAN1 from the embedded [wiki](https://embeded.readthedocs.io/en/latest/canbus/#configuring-the-bbb-can-interface). Make sure to use same bitrate in setup here and the CAN config in the [CME software](https://embeded.readthedocs.io/en/latest/canbus/#accelnet-serial-comms). 
2.	Connect to driver using serial. Reset the driver using CME to clear network errors. Also check bitrate and note the node ID.
3.	Open 3 terminals on BBB. On first terminal: `$ candump can1`

4.	2nd terminal: Navigate to canopend folder.

      ```
      $ cd CANopenSocket/canopend
      $ make
      $ app/canopend --help
      $ echo - > od6_storage
      $ echo - > od6_storage_auto
      $ app/canopend can1 -i 6 -s od6_storage -a od6_storage_auto
      ```

      Replace 6 with node address of driver, both for "od" and for "-i 6". Note: the "make" step is only required once. 

5. Ctrl+z, to start another process.
   
      ```
      $ bg
      $ app/canopend can1 -i 6 -c ""
      ```

5.	3rd terminal: navigate to canopencomm folder
   
      ```
      $ cd CANopenSocket/canopencomm
      $ make
      $ ./canopencomm –help
      ```
      Note: the "make" step is only required once.
6. `./canopencomm [1] 6 write 0x1017 0 i16 5000`
This can be used to set the heartbeat 1 every 5000ms. The 1st 6 is the node ID.
   
      ```
      $ ./canopencomm 6 preop
      $ ./canopencomm 6 start
      $ ./canopencomm 6 stop
      ```
      Above can be used to change driver states.


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
