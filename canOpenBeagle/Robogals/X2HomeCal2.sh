# HOMING
#!/bin/bash

#Power on with knee and hip fully bent back. Let go.


cd /home/debian/CANopenSocket/canopencomm

#Change drive mode to homing mode (mode 6).
./canopencomm [1] 2 write 0x6060 0 i8 6
./canopencomm [1] 1 write 0x6060 0 i8 6
./canopencomm [1] 3 write 0x6060 0 i8 6
./canopencomm [1] 4 write 0x6060 0 i8 6
#homing mode of operation: Home is current position. 
./canopencomm [1] 2 write 0x6098 0 i8 0
./canopencomm [1] 1 write 0x6098 0 i8 0
./canopencomm [1] 3 write 0x6098 0 i8 0
./canopencomm [1] 4 write 0x6098 0 i8 0

#Set home offset
./canopencomm [1] 2 write 0x607C 0 i32 0
./canopencomm [1] 1 write 0x607C 0 i32 0
./canopencomm [1] 3 write 0x607C 0 i32 0
./canopencomm [1] 4 write 0x607C 0 i32 0

#Set software joint limits
./canopencomm [1] 1 write 0x607D 1 i32 -- -110000 #Lhip lower limit
./canopencomm [1] 1 write 0x607D 2 i32 310000 #Lhip upper limit
./canopencomm [1] 2 write 0x607D 1 i32 2000 #Lknee lower limit
./canopencomm [1] 2 write 0x607D 2 i32 280000 #Lknee upper limit
./canopencomm [1] 3 write 0x607D 1 i32 -- -110000 #Rhip lower limit
./canopencomm [1] 3 write 0x607D 2 i32 310000 #Rhip upper limit
./canopencomm [1] 4 write 0x607D 1 i32 2000 #Rknee lower limit
./canopencomm [1] 4 write 0x607D 2 i32 280000 #Rknee upper limit

#Control word flip
./canopencomm [1] 2 write 0x6040 0 i16 15
./canopencomm [1] 2 write 0x6040 0 i16 31
./canopencomm [1] 2 write 0x6040 0 i16 15

./canopencomm [1] 4 write 0x6040 0 i16 15
./canopencomm [1] 4 write 0x6040 0 i16 31
./canopencomm [1] 4 write 0x6040 0 i16 15

./canopencomm [1] 3 write 0x6040 0 i16 15
./canopencomm [1] 3 write 0x6040 0 i16 31
./canopencomm [1] 3 write 0x6040 0 i16 15

./canopencomm [1] 1 write 0x6040 0 i16 15
./canopencomm [1] 1 write 0x6040 0 i16 31
./canopencomm [1] 1 write 0x6040 0 i16 15

./canopencomm 1 preop
./canopencomm 2 preop
./canopencomm 3 preop
./canopencomm 4 preop
