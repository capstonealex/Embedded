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

##Master Object Dictionary

In order to set up PDOs at the master end, an appropriate canopen object dictionary is needed.

This can be done by editing the eds in CANopenSocket. This must be edited to include any objects required to communicate with the nodes. The number of total PDOs must also be edited to account for all the nodes on the network. For example if you have 4 nodes each using 4 useful TPDOs, the master must have 16 RPDOs to recieve all the messages and map them to the appropriate objects.

In order to add an object to the dictionary, the desired addresses must be added and then the object must be defined.
The following shows an example of an EDS master mapping (Note: this is not the only way to map the objects required, it would be just as valid to make the motor the index and the various parameters the sub indeces. This is just an example of how it is implemented in the X2 with each node being mapped to its corresponding subindex for each object):

\[6040\]
ParameterName=Control words
ObjectType=9
SubNumber = 5

\[6040sub0\]
ParameterName=Number of Motors
ObjectType=7
DataType=5
AccessType=RO
PDOMapping=0
DefaultValue=4
LowLimit=4
HighLimit=4

\[6040sub1\]
ParameterName=Motor 1
ObjectType=7
DataType=6
AccessType=RW
PDOMapping=1

\[6040sub2\]
ParameterName=Motor 2
ObjectType=7
DataType=6
AccessType=RW
PDOMapping=1

\[6040sub3\]
ParameterName=Motor 3
ObjectType=7
DataType=6
AccessType=RW
PDOMapping=1

\[6040sub4\]
ParameterName=Motor 4
ObjectType=7
DataType=6
AccessType=RW
PDOMapping=1

For the index you must define the parameter name and subindex number. The object type for an object with sub indeces is always 9.

For the actual object entries the parameter name, object type (always 7 in this case), data type, access type and PDO mapping must be defined.

For PDO mapping to be accepted, the  PDO mapping must be equal to 1.

Data types can be found by referring to the node EDS. The common types encountered in this project were:
4 - Integer 32
5 - Unsigned 8
6 - Unsigned 16

Access type RW allows objects to be read and written. This is sufficient for most applications however other options such as RO (read only) can be used if required.

Using this edited EDS, the CO_OD.c/h files can be generated using openEDSeditor.

Once created, the CO_NO_NMT_MASTER parameter definition must be changed from 0 to 1.

##Master PDO Setup

Mapping the PDOs on the master could be done in an identical manner to the node mappings, although a better long term solution is to edit the CO_OD.c file to include the appropriate mappings by default.

In the CO_OD.c file, the PDO communication and mapping parameters for the first recieve PDO would appear as follows by default:

```c
/*1400*/ {{0x2L, 0x80000000L, 0xffL},
```
...
```c
/*1600*/ {{0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
```

These can be then mapped to the correct mapping by editing the parameters manually. Each element in the brackets corresponds to the subindeces of the object. in the example below, there are 2 objects mapped with index 6040 sub1 and 606C sub1 respectively (actual postion for motor 1 & actual velocity for motor 1) with a COB_ID. Note: the COB_ID of a RPDO on the master must match the COB_ID of the node TPDO it is expecting the information to come from.

```c
/*1400*/ {{0x2L, 0x0181L, 0xffL},
```
...
```c
/*1600*/ {{0x2L, 0x60640120L, 0x606c0120L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
```