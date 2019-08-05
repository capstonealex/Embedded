#!/bin/bash

cd /home/debian/CANopenSocket/canopencomm

#Go from preop to start mode
#./canopencomm 2 start
#./canopencomm 1 start

echo "current knee value"
./canopencomm [1] 4 read 0x6063 0 i32
echo "current hip value"
./canopencomm [1] 3 read 0x6063 0 i32