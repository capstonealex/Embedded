#!/bin/bash

#Power on with knee and hip fully bent back. Let go.


cd /home/debian/CANopenSocket/canopencomm

#Go from preop to start mode
./canopencomm 2 start
./canopencomm 1 start
./canopencomm 3 start
./canopencomm 4 start
#MOVING

#Change drive mode to position mode.
./canopencomm [1] 2 write 0x6060 0 i8 1
./canopencomm [1] 1 write 0x6060 0 i8 1
./canopencomm [1] 3 write 0x6060 0 i8 1
./canopencomm [1] 4 write 0x6060 0 i8 1
#Set current profile velocity
./canopencomm [1] 2 write 0x6081 0 i32 200000
./canopencomm [1] 1 write 0x6081 0 i32 200000
./canopencomm [1] 3 write 0x6081 0 i32 200000
./canopencomm [1] 4 write 0x6081 0 i32 200000
#Set current profile acceleration
./canopencomm [1] 2 write 0x6083 0 i32 30000
./canopencomm [1] 1 write 0x6083 0 i32 30000
./canopencomm [1] 3 write 0x6083 0 i32 30000
./canopencomm [1] 4 write 0x6083 0 i32 30000
#Set current profile deceleration
./canopencomm [1] 2 write 0x6084 0 i32 30000
./canopencomm [1] 1 write 0x6084 0 i32 30000
./canopencomm [1] 3 write 0x6084 0 i32 30000
./canopencomm [1] 4 write 0x6084 0 i32 30000
#set Target position
./canopencomm [1] 2 write 0x607A 0 i32 -- -280000
./canopencomm [1] 1 write 0x607A 0 i32 115000
./canopencomm [1] 4 write 0x607A 0 i32 -- -280000
./canopencomm [1] 3 write 0x607A 0 i32 115000

#move knee
./canopencomm [1] 2 write 0x6040 0 i16 47
./canopencomm [1] 2 write 0x6040 0 i16 63
./canopencomm [1] 2 write 0x6040 0 i16 47

./canopencomm [1] 1 write 0x6040 0 i16 47
./canopencomm [1] 1 write 0x6040 0 i16 63
./canopencomm [1] 1 write 0x6040 0 i16 47

./canopencomm [1] 4 write 0x6040 0 i16 47
./canopencomm [1] 4 write 0x6040 0 i16 63
./canopencomm [1] 4 write 0x6040 0 i16 47

./canopencomm [1] 3 write 0x6040 0 i16 47
./canopencomm [1] 3 write 0x6040 0 i16 63
./canopencomm [1] 3 write 0x6040 0 i16 47

