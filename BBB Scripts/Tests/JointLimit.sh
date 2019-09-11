#!/bin/bash

cd /home/debian/CANopenSocket/canopencomm


###################################################################################
#Go to Home

#Go from preop to start mode
./canopencomm 1 start
./canopencomm 2 start
./canopencomm 3 start
./canopencomm 4 start

echo "current Lhip value"
./canopencomm [1] 1 read 0x6063 0 i32
echo "current Lknee value"
./canopencomm [1] 2 read 0x6063 0 i32
echo "current Rhip value"
./canopencomm [1] 3 read 0x6063 0 i32
echo "current Rknee value"
./canopencomm [1] 4 read 0x6063 0 i32

#MOVING

#Change drive mode to position mode.
./canopencomm [1] 1 write 0x6060 0 i8 1
./canopencomm [1] 2 write 0x6060 0 i8 1
./canopencomm [1] 3 write 0x6060 0 i8 1
./canopencomm [1] 4 write 0x6060 0 i8 1
#Set current profile velocity
./canopencomm [1] 1 write 0x6081 0 i32 200000
./canopencomm [1] 2 write 0x6081 0 i32 200000
./canopencomm [1] 3 write 0x6081 0 i32 200000
./canopencomm [1] 4 write 0x6081 0 i32 200000
#Set current profile acceleration
./canopencomm [1] 1 write 0x6083 0 i32 30000
./canopencomm [1] 2 write 0x6083 0 i32 30000
./canopencomm [1] 3 write 0x6083 0 i32 30000
./canopencomm [1] 4 write 0x6083 0 i32 30000
#Set current profile deceleration
./canopencomm [1] 1 write 0x6084 0 i32 30000
./canopencomm [1] 2 write 0x6084 0 i32 30000
./canopencomm [1] 3 write 0x6084 0 i32 30000
./canopencomm [1] 4 write 0x6084 0 i32 30000
#set Target position
./canopencomm [1] 1 write 0x607A 0 i32 0
./canopencomm [1] 2 write 0x607A 0 i32 0
./canopencomm [1] 3 write 0x607A 0 i32 0
./canopencomm [1] 4 write 0x607A 0 i32 0

#move knee
./canopencomm [1] 1 write 0x6040 0 i16 47
./canopencomm [1] 1 write 0x6040 0 i16 63
./canopencomm [1] 2 write 0x6040 0 i16 47
./canopencomm [1] 2 write 0x6040 0 i16 63
./canopencomm [1] 3 write 0x6040 0 i16 47
./canopencomm [1] 3 write 0x6040 0 i16 63
./canopencomm [1] 4 write 0x6040 0 i16 47
./canopencomm [1] 4 write 0x6040 0 i16 63

echo "moving to home"

sleep 5s

echo "Probably Reached home"

echo "current Lhip value"
./canopencomm [1] 1 read 0x6063 0 i32
echo "current Lknee value"
./canopencomm [1] 2 read 0x6063 0 i32
echo "current Rhip value"
./canopencomm [1] 3 read 0x6063 0 i32
echo "current Rknee value"
./canopencomm [1] 4 read 0x6063 0 i32


###################################################################################
#set home as current position
./canopencomm [1] 1 write 0x6098 0 i8 0
./canopencomm [1] 2 write 0x6098 0 i8 0
./canopencomm [1] 3 write 0x6098 0 i8 0
./canopencomm [1] 4 write 0x6098 0 i8 0


#Read current software joint limits
./canopencomm [1] 1 read 0x607D 1 i32
./canopencomm [1] 1 read 0x607D 2 i32
./canopencomm [1] 2 read 0x607D 1 i32
./canopencomm [1] 2 read 0x607D 2 i32
./canopencomm [1] 3 read 0x607D 1 i32
./canopencomm [1] 3 read 0x607D 2 i32
./canopencomm [1] 4 read 0x607D 1 i32
./canopencomm [1] 5 read 0x607D 2 i32

#Set software joint limits
./canopencomm [1] 1 write 0x607D 1 i32 -- -110000 #Lhip lower limit
./canopencomm [1] 1 write 0x607D 2 i32 310000 #Lhip upper limit
./canopencomm [1] 2 write 0x607D 1 i32 2000 #Lknee lower limit
./canopencomm [1] 2 write 0x607D 2 i32 280000 #Lknee upper limit
./canopencomm [1] 3 write 0x607D 1 i32 -- -110000 #Rhip lower limit
./canopencomm [1] 3 write 0x607D 2 i32 310000 #Rhip upper limit
./canopencomm [1] 4 write 0x607D 1 i32 2000 #Rknee lower limit
./canopencomm [1] 4 write 0x607D 2 i32 280000 #Rknee upper limit

#Read current software joint limits
./canopencomm [1] 1 read 0x607D 1 i32
./canopencomm [1] 1 read 0x607D 2 i32
./canopencomm [1] 2 read 0x607D 1 i32
./canopencomm [1] 2 read 0x607D 2 i32
./canopencomm [1] 3 read 0x607D 1 i32
./canopencomm [1] 3 read 0x607D 2 i32
./canopencomm [1] 4 read 0x607D 1 i32
./canopencomm [1] 5 read 0x607D 2 i32

###################################################################################