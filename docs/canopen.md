# CANopen
## Resources to look into
 - Basics of CANopen

    https://www.ni.com/en-au/innovations/white-papers/13/the-basics-of-canopen.html

    Probably need OD (object dictionary) for constructing messages for particular devices.
    
    
 - Constructing Messages Manuallly

    http://robotsforroboticists.com/can-bus/ 
    
    See bottom of page. Probably can use this for cansend on can-utils (linux)
    
 - Video guide to CANopen

    https://www.youtube.com/watch?v=iIkBJ4NheCc

 - CAN-utils
    
    https://blog.mbedded.ninja/programming/operating-systems/linux/how-to-use-socketcan-with-the-command-line-in-linux/

    cansend and candump quick guide.

 - CMO for CANopen guide
    
    https://www.youtube.com/watch?v=NNlMBlTM228

    CMO is used by copley for CANopen comms. Most of the video is unusable since we are using a BBB for comms. But we maybe able to use the C++ code at the end to construct messages. 

 - CANopenSocket
   
    https://github.com/CANopenNode/CANopenSocket

    Linux tools for constructing/reading CANopen messages.

 - CANfestival
    https://basdebruijn.com/2015/05/sniffing-at-canopen/
    
    https://canfestival.org/

    Tools for CANopen.

- CANopen using python

    https://buildmedia.readthedocs.org/media/pdf/canopen/latest/canopen.pdf

    Python libraries for constructing CANopen messages.
