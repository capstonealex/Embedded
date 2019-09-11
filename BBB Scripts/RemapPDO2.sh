#!/bin/sh

#  Remap PDO.sh
#  
#  RECIEVE
#  Created by Robert Gadsby on 14/08/2019.
#
cd /home/debian/CANopenSocket/canopencomm

#TRANSMIT POS AND VEL

./canopencomm [1] 1 write 0x1801 1 u32 0x80000281
./canopencomm [1] 2 write 0x1801 1 u32 0x80000282
./canopencomm [1] 3 write 0x1801 1 u32 0x80000283
./canopencomm [1] 4 write 0x1801 1 u32 0x80000284

./canopencomm [1] 1 write 0x1A01 0 u8 0
./canopencomm [1] 1 write 0x1801 2 u8 1
./canopencomm [1] 1 write 0x1A01 1 u32 0x60640020
./canopencomm [1] 1 write 0x1A01 2 u32 0x606C0020
./canopencomm [1] 1 write 0x1A01 0 u8 2

./canopencomm [1] 2 write 0x1A01 0 u8 0
./canopencomm [1] 2 write 0x1801 2 u8 1
./canopencomm [1] 2 write 0x1A01 1 u32 0x60640020
./canopencomm [1] 2 write 0x1A01 2 u32 0x606C0020
./canopencomm [1] 2 write 0x1A01 0 u8 2

./canopencomm [1] 3 write 0x1A01 0 u8 0
./canopencomm [1] 3 write 0x1801 2 u8 1
./canopencomm [1] 3 write 0x1A01 1 u32 0x60640020
./canopencomm [1] 3 write 0x1A01 2 u32 0x606C0020
./canopencomm [1] 3 write 0x1A01 0 u8 2

./canopencomm [1] 4 write 0x1A01 0 u8 0
./canopencomm [1] 4 write 0x1801 2 u8 1
./canopencomm [1] 4 write 0x1A01 1 u32 0x60640020
./canopencomm [1] 4 write 0x1A01 2 u32 0x606C0020
./canopencomm [1] 4 write 0x1A01 0 u8 2

./canopencomm [1] 1 write 0x1801 1 u32 0x281
./canopencomm [1] 2 write 0x1801 1 u32 0x282
./canopencomm [1] 3 write 0x1801 1 u32 0x283
./canopencomm [1] 4 write 0x1801 1 u32 0x284

#TRANSMIT STATUS WORD

#./canopencomm [1] 1 write 0x1800 1 u32 0x80000181
#./canopencomm [1] 2 write 0x1800 1 u32 0x80000182
#./canopencomm [1] 3 write 0x1800 1 u32 0x80000183
#./canopencomm [1] 4 write 0x1800 1 u32 0x80000184

#./canopencomm [1] 1 write 0x1A00 0 u8 0
#./canopencomm [1] 1 write 0x1800 2 u8 0xFF
#./canopencomm [1] 1 write 0x1A00 1 u32 0x60410010
#./canopencomm [1] 1 write 0x1A00 0 u8 1

#./canopencomm [1] 2 write 0x1A00 0 u8 0
#./canopencomm [1] 2 write 0x1800 2 u8 0xFF
#./canopencomm [1] 2 write 0x1A00 1 u32 0x60410010
#./canopencomm [1] 2 write 0x1A00 0 u8 1

#./canopencomm [1] 3 write 0x1A00 0 u8 0
#./canopencomm [1] 3 write 0x1800 2 u8 0xFF
#./canopencomm [1] 3 write 0x1A00 1 u32 0x60410010
#./canopencomm [1] 3 write 0x1A00 0 u8 1

#./canopencomm [1] 4 write 0x1A00 0 u8 0
#./canopencomm [1] 4 write 0x1800 2 u8 0xFF
#./canopencomm [1] 4 write 0x1A00 1 u32 0x60410010
#./canopencomm [1] 4 write 0x1A00 0 u8 1

#./canopencomm [1] 1 write 0x1800 1 u32 0x181
#./canopencomm [1] 2 write 0x1800 1 u32 0x182
#./canopencomm [1] 3 write 0x1800 1 u32 0x183
#ß./canopencomm [1] 4 write 0x1800 1 u32 0x184

./canopencomm [1] 1 write 0x1800 1 u32 0x80000181
./canopencomm [1] 2 write 0x1800 1 u32 0x80000182
./canopencomm [1] 3 write 0x1800 1 u32 0x80000183
./canopencomm [1] 4 write 0x1800 1 u32 0x80000184

./canopencomm [1] 1 write 0x1A00 0 u8 0
./canopencomm [1] 1 write 0x1800 2 u8 0x01
./canopencomm [1] 1 write 0x1A00 1 u32 0x60770010
./canopencomm [1] 1 write 0x1A00 0 u8 1

./canopencomm [1] 2 write 0x1A00 0 u8 0
./canopencomm [1] 2 write 0x1800 2 u8 0x01
./canopencomm [1] 2 write 0x1A00 1 u32 0x60770010
./canopencomm [1] 2 write 0x1A00 0 u8 1

./canopencomm [1] 3 write 0x1A00 0 u8 0
./canopencomm [1] 3 write 0x1800 2 u8 0x01
./canopencomm [1] 3 write 0x1A00 1 u32 0x60770010
./canopencomm [1] 3 write 0x1A00 0 u8 1

./canopencomm [1] 4 write 0x1A00 0 u8 0
./canopencomm [1] 4 write 0x1800 2 u8 0x01
./canopencomm [1] 4 write 0x1A00 1 u32 0x60770010
./canopencomm [1] 4 write 0x1A00 0 u8 1

./canopencomm [1] 1 write 0x1800 1 u32 0x181
./canopencomm [1] 2 write 0x1800 1 u32 0x182
./canopencomm [1] 3 write 0x1800 1 u32 0x183
./canopencomm [1] 4 write 0x1800 1 u32 0x184

#RECIEVE POSITION COMMANDS

./canopencomm [1] 1 write 0x1401 1 u32 0x80000301
./canopencomm [1] 2 write 0x1401 1 u32 0x80000302
./canopencomm [1] 3 write 0x1401 1 u32 0x80000303
./canopencomm [1] 4 write 0x1401 1 u32 0x80000304

./canopencomm [1] 1 write 0x1601 0 u8 0
./canopencomm [1] 1 write 0x1401 2 u8 0xFF
./canopencomm [1] 1 write 0x1601 1 u32 0x607A0020
./canopencomm [1] 1 write 0x1601 0 u8 1

./canopencomm [1] 2 write 0x1601 0 u8 0
./canopencomm [1] 2 write 0x1401 2 u8 0xFF
./canopencomm [1] 2 write 0x1601 1 u32 0x607A0020
./canopencomm [1] 2 write 0x1601 0 u8 1

./canopencomm [1] 3 write 0x1601 0 u8 0
./canopencomm [1] 3 write 0x1401 2 u8 0xFF
./canopencomm [1] 3 write 0x1601 1 u32 0x607A0020
./canopencomm [1] 3 write 0x1601 0 u8 1

./canopencomm [1] 4 write 0x1601 0 u8 0
./canopencomm [1] 4 write 0x1401 2 u8 0xFF
./canopencomm [1] 4 write 0x1601 1 u32 0x607A0020
./canopencomm [1] 4 write 0x1601 0 u8 1

./canopencomm [1] 1 write 0x1401 1 u32 0x301
./canopencomm [1] 2 write 0x1401 1 u32 0x302
./canopencomm [1] 3 write 0x1401 1 u32 0x303
./canopencomm [1] 4 write 0x1401 1 u32 0x304

#RECIEVE VELOCITY COMMANDS

./canopencomm [1] 1 write 0x1402 1 u32 0x80000401
./canopencomm [1] 2 write 0x1402 1 u32 0x80000402
./canopencomm [1] 3 write 0x1402 1 u32 0x80000403
./canopencomm [1] 4 write 0x1402 1 u32 0x80000404

./canopencomm [1] 1 write 0x1602 0 u8 0
./canopencomm [1] 1 write 0x1402 2 u8 0xFF
./canopencomm [1] 1 write 0x1602 1 u32 0x60FF0020
./canopencomm [1] 1 write 0x1602 0 u8 1

./canopencomm [1] 2 write 0x1602 0 u8 0
./canopencomm [1] 2 write 0x1402 2 u8 0xFF
./canopencomm [1] 2 write 0x1602 1 u32 0x60FF0020
./canopencomm [1] 2 write 0x1602 0 u8 1

./canopencomm [1] 3 write 0x1602 0 u8 0
./canopencomm [1] 3 write 0x1402 2 u8 0xFF
./canopencomm [1] 3 write 0x1602 1 u32 0x60FF0020
./canopencomm [1] 3 write 0x1602 0 u8 1

./canopencomm [1] 4 write 0x1602 0 u8 0
./canopencomm [1] 4 write 0x1402 2 u8 0xFF
./canopencomm [1] 4 write 0x1602 1 u32 0x60FF0020
./canopencomm [1] 4 write 0x1602 0 u8 1

./canopencomm [1] 1 write 0x1402 1 u32 0x401
./canopencomm [1] 2 write 0x1402 1 u32 0x402
./canopencomm [1] 3 write 0x1402 1 u32 0x403
./canopencomm [1] 4 write 0x1402 1 u32 0x404

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

./canopencomm [1] 100 write 0x1604 1 u32 0x60410110
./canopencomm [1] 100 write 0x1605 1 u32 0x60410210
./canopencomm [1] 100 write 0x1606 1 u32 0x60410310
./canopencomm [1] 100 write 0x1607 1 u32 0x60410410

./canopencomm [1] 100 write 0x1604 0 u8 1
./canopencomm [1] 100 write 0x1605 0 u8 1
./canopencomm [1] 100 write 0x1606 0 u8 1
./canopencomm [1] 100 write 0x1607 0 u8 1

./canopencomm [1] 100 write 0x1404 1 u32 0x381
./canopencomm [1] 100 write 0x1405 1 u32 0x382
./canopencomm [1] 100 write 0x1406 1 u32 0x383
./canopencomm [1] 100 write 0x1407 1 u32 0x384

#Start nodes
./canopencomm [1] 1 start
./canopencomm [1] 2 start
./canopencomm [1] 3 start
./canopencomm [1] 4 start

#control word zero, so motors can move
./canopencomm [1] 1 write 0x6040 0 i16 0
./canopencomm [1] 2 write 0x6040 0 i16 0
./canopencomm [1] 3 write 0x6040 0 i16 0
./canopencomm [1] 4 write 0x6040 0 i16 0
