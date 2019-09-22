#!/bin/bash

#initialisation CAN interface

#setting up CAN1 interface on BBB.
sudo config-pin p9.24 can
sudo config-pin p9.26 can
sudo ip link set can1 up type can bitrate 1000000 &
sudo ifconfig can1 up &

#Create the OD storage files.
cd /home/debian/CANopenSocket/canopend

echo - > od4_storage &
echo - > od4_storage_auto &
