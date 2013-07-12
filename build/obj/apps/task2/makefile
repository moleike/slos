
# Task 2 base address 0x28000

CC = arm-elf-gcc
ASSEMBLER = arm-elf-as
LINKER = arm-elf-ld -Map ../../../image/map2.dat 
CONVERT = arm-elf-strip -O binary -o
CFLAGS = -mapcs -fomit-frame-pointer -O1 -c
ASFLAGS =

OBJS = start.o \
led.o \
startx.o \
swiapi.o


all : ${OBJS}
	${LINKER} -o ../../../image/apps/task2.elf linker.dat
	${CONVERT} ../../../image/apps/task2.bin -s ../../../image/apps/task2.elf

led.o : ../../../src/apps/task2/led.c
	${CC} ${CFLAGS} -o $@ $<

startx.o : ../../../src/apps/task2/startx.c
	${CC} ${CFLAGS} -o $@ $<

swiapi.o : ../../../src/apps/task2/swiapi.c
	${CC} ${CFLAGS} -o $@ $<

start.o : ../../../src/apps/task2/start.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<


