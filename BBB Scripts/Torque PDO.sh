#!/bin/sh

#  Torque PDO.sh
#  
#
#  Created by Robert Gadsby on 27/08/2019.
#

./canopencomm [1] 1 write 0x1802 1 u32 0x80000381
./canopencomm [1] 2 write 0x1802 1 u32 0x80000382
./canopencomm [1] 3 write 0x1802 1 u32 0x80000383
./canopencomm [1] 4 write 0x1802 1 u32 0x80000384

./canopencomm [1] 1 write 0x1A02 0 u8 0
./canopencomm [1] 1 write 0x1802 2 u8 0x01
./canopencomm [1] 1 write 0x1A02 1 u32 0x60770010
./canopencomm [1] 1 write 0x1A02 0 u8 1

./canopencomm [1] 2 write 0x1A02 0 u8 0
./canopencomm [1] 2 write 0x1802 2 u8 0x01
./canopencomm [1] 2 write 0x1A02 1 u32 0x60770010
./canopencomm [1] 2 write 0x1A02 0 u8 1

./canopencomm [1] 3 write 0x1A02 0 u8 0
./canopencomm [1] 3 write 0x1802 2 u8 0x01
./canopencomm [1] 3 write 0x1A02 1 u32 0x60770010
./canopencomm [1] 3 write 0x1A02 0 u8 1

./canopencomm [1] 4 write 0x1A02 0 u8 0
./canopencomm [1] 4 write 0x1802 2 u8 0x01
./canopencomm [1] 4 write 0x1A02 1 u32 0x60770010
./canopencomm [1] 4 write 0x1A02 0 u8 1

./canopencomm [1] 1 write 0x1802 1 u32 0x381
./canopencomm [1] 2 write 0x1802 1 u32 0x382
./canopencomm [1] 3 write 0x1802 1 u32 0x383
./canopencomm [1] 4 write 0x1802 1 u32 0x384

./canopencomm [1] 100 write 0x1604 1 u32 0x60770110
./canopencomm [1] 100 write 0x1605 1 u32 0x60770210
./canopencomm [1] 100 write 0x1606 1 u32 0x60770310
./canopencomm [1] 100 write 0x1607 1 u32 0x60770410

./canopencomm [1] 100 write 0x1604 0 u8 1
./canopencomm [1] 100 write 0x1605 0 u8 1
./canopencomm [1] 100 write 0x1606 0 u8 1
./canopencomm [1] 100 write 0x1607 0 u8 1

./canopencomm [1] 100 write 0x1404 1 u32 0x381
./canopencomm [1] 100 write 0x1405 1 u32 0x382
./canopencomm [1] 100 write 0x1406 1 u32 0x383
./canopencomm [1] 100 write 0x1407 1 u32 0x384


