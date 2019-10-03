#!/bin/bash

cd /home/debian/CANopenSocket/canopencomm

echo "LHip, Lknee, Rhip, Rknee"

#Go from preop to start mode
./canopencomm [1] 1 read 0x6041 0 i16
./canopencomm [1] 2 read 0x6041 0 i16
./canopencomm [1] 3 read 0x6041 0 i16
./canopencomm [1] 4 read 0x6041 0 i16

# manufacturer status error
./canopencomm [1] 1 read 0x1002 0 i32
./canopencomm [1] 2 read 0x1002 0 i32
./canopencomm [1] 3 read 0x1002 0 i32
./canopencomm [1] 4 read 0x1002 0 i32