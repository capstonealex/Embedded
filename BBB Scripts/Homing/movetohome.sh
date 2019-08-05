#!/bin/bash

#left knee (node 2), position mode, velocity control.

cd /home/debian/CANopenSocket/canopencomm

#Go from preop to start mode
./canopencomm 2 start
./canopencomm 1 start

echo "current knee value"
./canopencomm [1] 2 read 0x6063 0 i32
echo "current hip value"
./canopencomm [1] 1 read 0x6063 0 i32

#MOVING

#Change drive mode to position mode.
./canopencomm [1] 2 write 0x6060 0 i8 1
./canopencomm [1] 1 write 0x6060 0 i8 1
#Set current profile velocity
./canopencomm [1] 2 write 0x6081 0 i32 200000
./canopencomm [1] 1 write 0x6081 0 i32 200000
#Set current profile acceleration
./canopencomm [1] 2 write 0x6083 0 i32 30000
./canopencomm [1] 1 write 0x6083 0 i32 30000
#Set current profile deceleration
./canopencomm [1] 2 write 0x6084 0 i32 30000
./canopencomm [1] 1 write 0x6084 0 i32 30000
#set Target position
./canopencomm [1] 2 write 0x607A 0 i32 0
./canopencomm [1] 1 write 0x607A 0 i32 0

#move knee
./canopencomm [1] 2 write 0x6040 0 i16 47
./canopencomm [1] 2 write 0x6040 0 i16 63
./canopencomm [1] 1 write 0x6040 0 i16 47
./canopencomm [1] 1 write 0x6040 0 i16 63

echo "moving to home"

sleep 5s

echo "Reached home"

echo "current knee value"
./canopencomm [1] 2 read 0x6063 0 i32
echo "current hip value"
./canopencomm [1] 1 read 0x6063 0 i32