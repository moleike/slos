
# Base load address 0x30000

CC = arm-elf-gcc
ASSEMBLER = arm-elf-as
LINKER = arm-elf-ld -Map ../../../image/map.dat 
CONVERT = arm-elf-strip -O binary -o
CFLAGS = -mapcs -fomit-frame-pointer -O1 -c
ASFLAGS =

OBJS = start.o \
serial.o \
com.o \
shell.o \
readline.o \
swiapi.o \
startx.o 


all : ${OBJS}
	${LINKER} -o ../../../image/apps/task3.elf linker.dat
	${CONVERT} ../../../image/apps/task3.bin -s ../../../image/apps/task3.elf

startx.o : ../../../src/apps/task3/startx.c
	${CC} ${CFLAGS} -o $@ $<

start.o : ../../../src/apps/task3/start.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<

serial.o : ../../../src/apps/task3/serial.c
	${CC} ${CFLAGS} -o $@ $<

shell.o : ../../../src/apps/task3/shell.c
	${CC} ${CFLAGS} -o $@ $<
 
com.o : ../../../src/apps/task3/com.c
	${CC} ${CFLAGS} -o $@ $<

readline.o : ../../../src/apps/task3/readline.c
	${CC} ${CFLAGS} -o $@ $<

swiapi.o : ../../../src/apps/task3/swiapi.c
	${CC} ${CFLAGS} -o $@ $<

