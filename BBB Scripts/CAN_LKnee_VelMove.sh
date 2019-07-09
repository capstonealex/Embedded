#!/bin/bash

cd /home/debian/CANopenSocket/canopencomm

#Go from preop to start mode
./canopencomm 2 start

#Change drive mode to position mode.
./canopencomm [1] 2 write 0x6060 0 i8 3

#Display current drive mode
./canopencomm [1] 2 read 0x6061 0 i8

#display current knee position value
echo "current knee position"
./canopencomm [1] 2 read 0x6063 0 i32

#display current knee velocity
echo "current knee velocity"
./canopencomm [1] 2 read 0x606C 0 i32

#set acceleration value
./canopencomm [1] 2 write 0x6083 0 i32 10

#set deceleration value
./canopencomm [1] 2 write 0x6084 0 i32 10

#set target velocity. Initiates motion.
./canopencomm [1] 2 write 0x60FF 0 i32 10
sleep 2s
./canopencomm [1] 2 write 0x60FF 0 i32 0

#halt using control word
./canopencomm [1] 2 write 0x6040 0 i16 271
