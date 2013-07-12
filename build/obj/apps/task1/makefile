
# Task 1 base address 0x20000

CC = arm-elf-gcc
ASSEMBLER = arm-elf-as
LINKER = arm-elf-ld -Map ../../../image/map1.dat 
CONVERT = arm-elf-strip -O binary -o
CFLAGS = -mapcs -fomit-frame-pointer -O1 -c
ASFLAGS =

OBJS = start.o \
led.o \
startx.o \
swiapi.o


all : ${OBJS}
	${LINKER} -o ../../../image/apps/task1.elf linker.dat
	${CONVERT} ../../../image/apps/task1.bin -s ../../../image/apps/task1.elf

start.o : ../../../src/apps/task1/start.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<

led.o : ../../../src/apps/task1/led.c
	${CC} ${CFLAGS} -o $@ $<

 
startx.o : ../../../src/apps/task1/startx.c
	${CC} ${CFLAGS} -o $@ $<

swiapi.o : ../../../src/apps/task1/swiapi.c
	${CC} ${CFLAGS} -o $@ $<


