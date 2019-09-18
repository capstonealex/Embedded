#!/bin/bash

#cd /home/debian/CANopenSocket/canopend

#today=`date '+%Y_%m_%d__%H_%M_%S'`;

echo "Enter name for prev log file (also extension)"
read newname

filename="X2_log.txt"

mv $filename $newname
