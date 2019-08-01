#!/bin/bash

#left knee (node 2), position mode, velocity control.

cd /home/debian/CANopenSocket/canopencomm

#Go from preop to start mode
./canopencomm 1 start
./canopencomm 2 start
./canopencomm 3 start
./canopencomm 4 start

#Change drive mode to position mode.
./canopencomm [1] 1 write 0x6060 0 i8 1
./canopencomm [1] 2 write 0x6060 0 i8 1
./canopencomm [1] 3 write 0x6060 0 i8 1
./canopencomm [1] 4 write 0x6060 0 i8 1

#Read current profile velocity
echo "Current profile velocity"
#./canopencomm [1] 2 read 0x6081 0 i32
./canopencomm [1] 1 write 0x6081 0 i32 300000
./canopencomm [1] 2 write 0x6081 0 i32 300000
./canopencomm [1] 3 write 0x6081 0 i32 300000
./canopencomm [1] 4 write 0x6081 0 i32 300000

#Read current profile acceleration
echo "Current profile acceleration"
#./canopencomm [1] 2 read 0x6083 0 i32
./canopencomm [1] 2 write 0x6083 0 i32 50000
./canopencomm [1] 1 write 0x6083 0 i32 50000
./canopencomm [1] 2 write 0x6083 0 i32 50000
./canopencomm [1] 1 write 0x6083 0 i32 50000

#Read current profile deceleration
echo "Current profile deceleration"
#./canopencomm [1] 2 read 0x6084 0 i32
./canopencomm [1] 1 write 0x6084 0 i32 50000
./canopencomm [1] 2 write 0x6084 0 i32 50000
./canopencomm [1] 3 write 0x6084 0 i32 50000
./canopencomm [1] 4 write 0x6084 0 i32 50000

#Read current profile type
#echo "Current profile type (0 is trapz, 3 is S, -1 is Vel)"
#./canopencomm [1] 2 read 0x6086 0 i16

#Trajectory Jerk Limit
#echo "Current jerk limit for S type"
#./canopencomm [1] 2 read 0x2121 0 i32

#display current knee value
#echo "current knee value"
#./canopencomm [1] 2 read 0x6063 0 i32

#Set target position
#echo "Enter target absolute position (0 is full extended, 240,000 is bent):"
#read target
#./canopencomm [1] 2 write 0x607A 0 i32 $target
./canopencomm [1] 1 write 0x607A 0 i32 100000
./canopencomm [1] 2 write 0x607A 0 i32 100000
./canopencomm [1] 3 write 0x607A 0 i32 100000
./canopencomm [1] 4 write 0x607A 0 i32 100000

#move knee
./canopencomm [1] 1 write 0x6040 0 i16 47
./canopencomm [1] 1 write 0x6040 0 i16 63
#./canopencomm [1] 2 write 0x6040 0 i16 47

./canopencomm [1] 2 write 0x6040 0 i16 47
./canopencomm [1] 2 write 0x6040 0 i16 63
#./canopencomm [1] 1 write 0x6040 0 i16 47

./canopencomm [1] 3 write 0x6040 0 i16 47
./canopencomm [1] 3 write 0x6040 0 i16 63
#./canopencomm [1] 2 write 0x6040 0 i16 47

./canopencomm [1] 4 write 0x6040 0 i16 47
./canopencomm [1] 4 write 0x6040 0 i16 63
#./canopencomm [1] 1 write 0x6040 0 i16 47

#sleep 1s

#go to preop
#./canopencomm 2 preop