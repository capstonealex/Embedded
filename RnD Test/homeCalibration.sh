#!/bin/bash

#Power on with knee and hip fully bent back. Let go.
#Then run this script.

echo "WARNING:"
echo "Run this script only if you powered on Exo with knee and hip fully bent back."
echo "Do you want to proceed(y/n):"
read answer

if [ "$answer" != "y" ]
then 
	echo "Exiting"
	exit
fi

cd /home/debian/CANopenSocket/canopencomm

#Go from preop to start mode
./canopencomm 2 start
./canopencomm 1 start
./canopencomm 3 start
./canopencomm 4 start

echo "current left knee value"
./canopencomm [1] 2 read 0x6063 0 i32
echo "current left hip value"
./canopencomm [1] 1 read 0x6063 0 i32
echo "current right knee value"
./canopencomm [1] 4 read 0x6063 0 i32
echo "current right hip value"
./canopencomm [1] 3 read 0x6063 0 i32

#MOVING

#Change drive mode to position mode.
./canopencomm [1] 2 write 0x6060 0 i8 1
./canopencomm [1] 1 write 0x6060 0 i8 1
./canopencomm [1] 3 write 0x6060 0 i8 1
./canopencomm [1] 4 write 0x6060 0 i8 1
#Set current profile velocity
./canopencomm [1] 2 write 0x6081 0 i32 200000
./canopencomm [1] 1 write 0x6081 0 i32 200000
./canopencomm [1] 3 write 0x6081 0 i32 200000
./canopencomm [1] 4 write 0x6081 0 i32 200000
#Set current profile acceleration
./canopencomm [1] 2 write 0x6083 0 i32 30000
./canopencomm [1] 1 write 0x6083 0 i32 30000
./canopencomm [1] 3 write 0x6083 0 i32 30000
./canopencomm [1] 4 write 0x6083 0 i32 30000
#Set current profile deceleration
./canopencomm [1] 2 write 0x6084 0 i32 30000
./canopencomm [1] 1 write 0x6084 0 i32 30000
./canopencomm [1] 3 write 0x6084 0 i32 30000
./canopencomm [1] 4 write 0x6084 0 i32 30000
#set Target position
./canopencomm [1] 2 write 0x607A 0 i32 -- -280000
./canopencomm [1] 1 write 0x607A 0 i32 115000
./canopencomm [1] 4 write 0x607A 0 i32 -- -280000
./canopencomm [1] 3 write 0x607A 0 i32 115000

#move knee
./canopencomm [1] 2 write 0x6040 0 i16 47
./canopencomm [1] 2 write 0x6040 0 i16 63
./canopencomm [1] 2 write 0x6040 0 i16 47

./canopencomm [1] 1 write 0x6040 0 i16 47
./canopencomm [1] 1 write 0x6040 0 i16 63
./canopencomm [1] 1 write 0x6040 0 i16 47

./canopencomm [1] 4 write 0x6040 0 i16 47
./canopencomm [1] 4 write 0x6040 0 i16 63
./canopencomm [1] 4 write 0x6040 0 i16 47

./canopencomm [1] 3 write 0x6040 0 i16 47
./canopencomm [1] 3 write 0x6040 0 i16 63
./canopencomm [1] 3 write 0x6040 0 i16 47

echo "Going to home"

sleep 10s

echo "current knee value"
./canopencomm [1] 2 read 0x6063 0 i32
echo "current hip value"
./canopencomm [1] 1 read 0x6063 0 i32
echo "current knee value"
./canopencomm [1] 3 read 0x6063 0 i32
echo "current hip value"
./canopencomm [1] 4 read 0x6063 0 i32

echo "Reached home. Homing now"

# HOMING

#Change drive mode to homing mode (mode 6).
./canopencomm [1] 2 write 0x6060 0 i8 6
./canopencomm [1] 1 write 0x6060 0 i8 6
./canopencomm [1] 3 write 0x6060 0 i8 6
./canopencomm [1] 4 write 0x6060 0 i8 6
#homing mode of operation: Home is current position. 
./canopencomm [1] 2 write 0x6098 0 i8 0
./canopencomm [1] 1 write 0x6098 0 i8 0
./canopencomm [1] 3 write 0x6098 0 i8 0
./canopencomm [1] 4 write 0x6098 0 i8 0

#Set home offset
./canopencomm [1] 2 write 0x607C 0 i32 0
./canopencomm [1] 1 write 0x607C 0 i32 0
./canopencomm [1] 3 write 0x607C 0 i32 0
./canopencomm [1] 4 write 0x607C 0 i32 0

#Set software joint limits
./canopencomm [1] 1 write 0x607D 1 i32 -- -110000 #Lhip lower limit
./canopencomm [1] 1 write 0x607D 2 i32 310000 #Lhip upper limit
./canopencomm [1] 2 write 0x607D 1 i32 2000 #Lknee lower limit
./canopencomm [1] 2 write 0x607D 2 i32 280000 #Lknee upper limit
./canopencomm [1] 3 write 0x607D 1 i32 -- -110000 #Rhip lower limit
./canopencomm [1] 3 write 0x607D 2 i32 310000 #Rhip upper limit
./canopencomm [1] 4 write 0x607D 1 i32 2000 #Rknee lower limit
./canopencomm [1] 4 write 0x607D 2 i32 280000 #Rknee upper limit

#Control word flip
./canopencomm [1] 2 write 0x6040 0 i16 15
./canopencomm [1] 2 write 0x6040 0 i16 31
./canopencomm [1] 2 write 0x6040 0 i16 15

./canopencomm [1] 4 write 0x6040 0 i16 15
./canopencomm [1] 4 write 0x6040 0 i16 31
./canopencomm [1] 4 write 0x6040 0 i16 15

./canopencomm [1] 3 write 0x6040 0 i16 15
./canopencomm [1] 3 write 0x6040 0 i16 31
./canopencomm [1] 3 write 0x6040 0 i16 15

./canopencomm [1] 1 write 0x6040 0 i16 15
./canopencomm [1] 1 write 0x6040 0 i16 31
./canopencomm [1] 1 write 0x6040 0 i16 15

echo "current left knee value"
./canopencomm [1] 2 read 0x6063 0 i32
echo "current left hip value"
./canopencomm [1] 1 read 0x6063 0 i32
echo "current right knee value"
./canopencomm [1] 4 read 0x6063 0 i32
echo "current right hip value"
./canopencomm [1] 3 read 0x6063 0 i32

#Setting motors to preop
echo "Motors to preop"									  
./canopencomm 1 preop
./canopencomm 2 preop
./canopencomm 3 preop
./canopencomm 4 preop