#!/bin/bash

cd /home/debian/CANopenSocket/canopencomm


#echo "Tracking Window"
./canopencomm [1] 1 write 0x6067 0 i32 10000
./canopencomm [1] 2 write 0x6067 0 i32 10000
./canopencomm [1] 3 write 0x6067 0 i32 10000
./canopencomm [1] 4 write 0x6067 0 i32 10000

#deafult was 2048
echo "Tracking Window"
./canopencomm [1] 1 read 0x6067 0 i32
./canopencomm [1] 2 read 0x6067 0 i32
./canopencomm [1] 3 read 0x6067 0 i32
./canopencomm [1] 4 read 0x6067 0 i32
#echo "Tracking window time"
#./canopencomm [1] 1 read 0x6068 0 i16
#./canopencomm [1] 2 read 0x6068 0 i16
#./canopencomm [1] 3 read 0x6068 0 i16
#./canopencomm [1] 4 read 0x6068 0 i16

#deafult was 1000
echo "Position gain"
./canopencomm [1] 1 write 0x60FB 1 i16 5000
./canopencomm [1] 2 write 0x60FB 1 i16 5000
./canopencomm [1] 3 write 0x60FB 1 i16 5000
./canopencomm [1] 4 write 0x60FB 1 i16 5000

echo "Position gain"
./canopencomm [1] 1 read 0x60FB 1 i16
./canopencomm [1] 2 read 0x60FB 1 i16
./canopencomm [1] 3 read 0x60FB 1 i16
./canopencomm [1] 4 read 0x60FB 1 i16

#echo "Integral gain"
#./canopencomm [1] 1 read 0x60FB 5 i16
#./canopencomm [1] 2 read 0x60FB 5 i16
#./canopencomm [1] 3 read 0x60FB 5 i16
#./canopencomm [1] 4 read 0x60FB 5 i16

#echo "Clear Knee Error"
#./canopencomm [1] 4 write 0x2183 0 i32 512
#./canopencomm [1] 2 write 0x2183 0 i32 512
#./canopencomm [1] 4 write 0x6040 0 i16 64
#./canopencomm [1] 4 write 0x6040 0 i16 47

#echo "Torque limit Word"
#./canopencomm [1] 1 read 0x2384 3 i16
#./canopencomm [1] 2 read 0x60E0 0 i16
#./canopencomm [1] 3 read 0x60E0 0 i16
#./canopencomm [1] 4 read 0x60E0 0 i16

echo "Status Word"
./canopencomm [1] 1 read 0x6041 0 i16
./canopencomm [1] 2 read 0x6041 0 i16
./canopencomm [1] 3 read 0x6041 0 i16
./canopencomm [1] 4 read 0x6041 0 i16