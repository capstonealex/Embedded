#!/bin/bash

cd /home/debian/CANopenSocket/canopencomm

#Go from preop to start mode
./canopencomm [1] 100 write 0x1006 0 u32 1000000 #1s=1000000