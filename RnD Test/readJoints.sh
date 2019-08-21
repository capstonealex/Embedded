#!/bin/bash

cd /home/debian/CANopenSocket/canopencomm

#Go from preop to start mode
#./canopencomm 2 start
#./canopencomm 1 start

echo "current Lknee value"
./canopencomm [1] 4 read 0x6063 0 i32
echo "current Lhip value"
./canopencomm [1] 3 read 0x6063 0 i32
echo "current Rknee value"
./canopencomm [1] 2 read 0x6063 0 i32
echo "current Rhip value"
./canopencomm [1] 1 read 0x6063 0 i32