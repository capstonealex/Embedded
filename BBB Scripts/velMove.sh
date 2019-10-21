#!/bin/bash

cd /home/debian/CANopenSocket/canopencomm

#Go from preop to start mode
./canopencomm 2 start

#Change drive mode to velocity mode.
./canopencomm [1] 2 write 0x6060 0 i8 3

./canopencomm [1] 2 write 0x6040 0 i16 15
./canopencomm [1] 2 write 0x6040 0 i16 31

#set acceleration value
./canopencomm [1] 2 write 0x6083 0 i32 100000

#set deceleration value
./canopencomm [1] 2 write 0x6084 0 i32 100000

#set target velocity. Initiates motion.
./canopencomm [1] 2 write 0x60FF 0 i32 500000

sleep 3s

./canopencomm [1] 2 write 0x60FF 0 i32 0

#halt using control word
./canopencomm [1] 2 write 0x6040 0 i16 271
