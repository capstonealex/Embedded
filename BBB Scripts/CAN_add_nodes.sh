#!/bin/bash
cd /home/debian/CANopenSocket/canopend

# & at the end is used to run processes in background

#adding nodes
#node 1
echo - > od1_storage
echo - > od1_storage_auto
app/canopend can1 -i 1 -s od1_storage -a od1_storage_auto &

#node 2
echo - > od2_storage
echo - > od2_storage_auto
app/canopend can1 -i 2 -s od2_storage -a od2_storage_auto &

#master
#using node ID 0 throws error. Use 100 for now. 
app/canopend can1 -i 100 -c ""
