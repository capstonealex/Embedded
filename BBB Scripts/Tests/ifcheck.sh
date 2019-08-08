#!/bin/bash

#Power on with knee and hip fully bent back. Let go.
#Then run this script.

echo "Enter yes or no"
read answer

if [ "$answer" == "yes" ]
then 
	echo "Entered yes"
elif [ "$answer" == "no" ]
then 
	echo "Entered no"
	exit
else 
	echo "y u no listen"
fi

echo "Reached end" 