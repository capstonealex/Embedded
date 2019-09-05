#!/bin/sh

#  pdotest1.sh
#
#
#  Created by Robert Gadsby on 30/07/2019.
#  


./canopencomm [1] 1 preop

./canopencomm [1] 1 write 0x1801 1 u32 2147483648

./canopencomm [1] 1 write 0x1A01 0 u8 0

./canopencomm [1] 1 write 0x1801 2 u8 253

./canopencomm [1] 1 write 0x1A01 1 u32 1617166368

./canopencomm [1] 1 write 0x1A01 2 u32 1617690656

./canopencomm [1] 1 write 0x1A01 0 u8 2

./canopencomm [1] 1 write 0x1801 1 u32 897

./canopencomm [1] 1 start

cansend can1 181#R

cansend can1 281#R

cansend can1 381#R





