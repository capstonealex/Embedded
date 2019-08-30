#Process Data Objects (PDOs)

##Configuring PDOs on nodes

This will detail how to configure the nodes PDO messaging protocol using SDO messaging from canopend

The basic steps for PDO reconfiguration are as follows:

1. Enable the 31st bit of the associated can object id (index 0x140N sub index 1 for recieve PDO's and index 0x180N sub index 1 for transmit PDO's) by setting it to 0x80000000 - This is required to alter any parameter of the PDO.
2. Set 0x160N sub 0 (for RPDO) or 0x1A0N sub 0 (for TPDO) to 0 - This is required to change any mapping parameters.
3. Set 0x140N sub 2 (RPDO) or 0x180N sub 2 (TPDO) to the desired communication mode:
    * 0-240 - the recieved data is held until the next sync message before applying the data to the object. (RPDO)
    * 241-253 - reserved. (RPDO)
    * 254-255 - Recieved data is applied to the object immediately upon reception. (RPDO)
    * 0 - PDO is transmitted on the next sync message following a pdo event - note very few objects in the nodes can trigger a PDO event. (TPDO)
    * 1-240 - the PDO is transmitted every n sync messages, where n is the communication mode value (use 1 for every sync). (TPDO)
    * 241-251 - reserved. (TPDO)
    * 252 - PDO transmitted on next sync after a remote transmission request (RTR). (TPDO)
    * 253 - PDO is transmitted immediately after RTR. (TPDO)
    * 254-255 - PDO is transmitted immediately following an internal PDO event. (TPDO)
4. To map n objects to the PDO change the mapping parameters 0x160N sub 1 to n (RPDO) or 0x1A0N sub 1 to n (TPDO) as follows:
    * Bits 0-7 are the size of the data to be mapped
    * Bits 8-15 are the sub-index of the data to be mapped
    * Bits 16-31 are the index of the data
    * For example: to map an object of address 0x1234 sub index 5 with a size of 16bit, you would change the value of the mapping parameter to 0x12340510
    Note: Each PDO has a maximum data size of 8Byte (64bit) so make sure the total mapped parameters are less than this or mapping will fail.
5. Set 0x160N sub 0 (for RPDO) or 0x1A0N sub 0 (for TPDO) to the number of mapped parameters in the PDO.
6. Disable the 31st bit of 0x180N sub 1 to enable pdo and set the COB_ID. The defaults for the COB_IDs are as follows:
    * 0x1400: 0x200+nodeid
    * 0x1401: 0x300+nodeid
    * 0x1402: 0x400+nodeid
    * 0x1403: 0x500+nodeid
    * 0x1800: 0x180+nodeid
	* 0x1801: 0x280+nodeid
	* 0x1802: 0x380+nodeid
	* 0x1803: 0x480+nodeid

For the purposes of the X2, the following objects are mapped using the following mapping parameters:
TPDOs:
1. Status word (0x60410010).
2. Actual position (0x60640020), Actual Velocity (0x606C0020).
3. Actual Torque (0x60770010).
RPDOs:
1. Control Word (0x60400010).
2. Control Word (0x60400010), Target Position (0x607A0020).
3. Control Word (0x60400010), Target Velocity (0x60FF0020).

For the X2 the actual position and velocity are set up to be sent out at a rate of 1000Hz. In order to do this, the  communication mode for each TPDO is set to 1 and a sync message is set up at 1000Hz.

##Initialising Sync Message

Initialising the sync message is done in 2 steps and can be on any node you desire, provided it is capable of producing a sync message.
- Set 0x1005 sub 0 to 0x40000080.
- Set 0x1006 sub 0 to 1000. (Time period in microseconds)