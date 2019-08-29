#!/bin/bash

#knee and hip positions are hardcoded. Use with care as home position is whatever startup position is. Take care not to exceed joint limits.

cd /home/debian/CANopenSocket/canopencomm

#Go from preop to start mode
./canopencomm 1 start
./canopencomm 2 start

#Change drive mode to position mode.
./canopencomm [1] 1 write 0x6060 0 i8 1
./canopencomm [1] 2 write 0x6060 0 i8 1

#Display current drive mode
echo "Drive mode for hip and knee:"
./canopencomm [1] 1 read 0x6061 0 i8
./canopencomm [1] 2 read 0x6061 0 i8

#display current position
echo "current knee position"
./canopencomm [1] 1 read 0x6063 0 i32

echo "current hip position"
./canopencomm [1] 2 read 0x6063 0 i32

#Set target position
./canopencomm [1] 1 write 0x607A 0 i32 200000
./canopencomm [1] 2 write 0x607A 0 i32 200000

#move hip
./canopencomm [1] 1 write 0x6040 0 i16 47
./canopencomm [1] 1 write 0x6040 0 i16 63

#move knee
./canopencomm [1] 2 write 0x6040 0 i16 47
./canopencomm [1] 2 write 0x6040 0 i16 63

#display current knee value
echo "current knee value"
./canopencomm [1] 1 read 0x6063 0 i32
echo "current knee value"
./canopencomm [1] 2 read 0x6063 0 i32

sleep 3s

#Set target position
./canopencomm [1] 1 write 0x607A 0 i32 0
./canopencomm [1] 2 write 0x607A 0 i32 2000

#move hip
./canopencomm [1] 1 write 0x6040 0 i16 47
./canopencomm [1] 1 write 0x6040 0 i16 63

#move knee
./canopencomm [1] 2 write 0x6040 0 i16 47
./canopencomm [1] 2 write 0x6040 0 i16 63

#display current knee value
echo "current knee value"
./canopencomm [1] 1 read 0x6063 0 i32
echo "current knee value"
./canopencomm [1] 2 read 0x6063 0 i32