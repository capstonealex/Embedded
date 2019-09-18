#!/bin/bash

#initialisation of Virtual CAN interface and CANopen nodes for 
#testing of socket connections.

#setting up CAN1 interface on BBB.
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0


#Setting up slave nodes
cd /home/debian/CANopenSocket/canopend

#Setting up master node
echo - > od100_storage
echo - > od100_storage_auto
app/canopend vcan0 -i 100 -s od100_storage -a od100_storage_auto -c "" 