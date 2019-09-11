#!/bin/bash



#Setting up slave nodes
cd /home/debian/CANopenSocket/canopend

echo - > od1_storage
echo - > od1_storage_auto
app/canopend vcan0 -i 1 -s od1_storage -a od1_storage_auto&

echo - > od2_storage
echo - > od2_storage_auto
app/canopend vcan0 -i 2 -s od2_storage -a od2_storage_auto&

cd /home/debian/CANopenSocket/canopencomm
./canopencomm [1] 1 write 0x1017 0 i16 1000
./canopencomm [1] 2 write 0x1017 0 i16 1000
./canopencomm [1] 100 write 0x1017 0 i16 1000