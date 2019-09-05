#!/bin/sh

#  PDO scripting.sh
#  
#
#  Created by Robert Gadsby on 30/07/2019.
#  

./canopencomm [1] 1 preop

./canopencomm [1] 2 preop

./canopencomm [1] 3 preop

./canopencomm [1] 4 preop

./canopencomm [1] 1 write 0x1803 1 u32 2147483648

./canopencomm [1] 1 write 0x1A03 0 u8 0

./canopencomm [1] 1 write 0x1803 2 u8 253

./canopencomm [1] 1 write 0x1A03 0 u8 2

./canopencomm [1] 1 write 0x1803 1 u32 897

./canopencomm [1] 2 write 0x1803 1 u32 2147483648

./canopencomm [1] 2 write 0x1A03 0 u8 0

./canopencomm [1] 2 write 0x1803 2 u8 253

./canopencomm [1] 2 write 0x1A03 0 u8 2

./canopencomm [1] 2 write 0x1803 1 u32 897

./canopencomm [1] 3 write 0x1803 1 u32 2147483648

./canopencomm [1] 3 write 0x1A03 0 u8 0

./canopencomm [1] 3 write 0x1803 2 u8 253

./canopencomm [1] 3 write 0x1A03 0 u8 2

./canopencomm [1] 3 write 0x1803 1 u32 897

./canopencomm [1] 4 write 0x1803 1 u32 2147483648

./canopencomm [1] 4 write 0x1A03 0 u8 0

./canopencomm [1] 4 write 0x1803 2 u8 253

./canopencomm [1] 4 write 0x1A03 0 u8 2

./canopencomm [1] 4 write 0x1803 1 u32 897

./canopencomm [1] 1 start

./canopencomm [1] 2 start

./canopencomm [1] 3 start

./canopencomm [1] 4 start

cansend can1 381#R

cansend can1 382#R

cansend can1 383#R

cansend can1 384#R
