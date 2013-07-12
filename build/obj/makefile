CC = arm-elf-gcc
ASSEMBLER = arm-elf-as
LINKER = arm-elf-ld -Map ../image/map.dat 
CONVERT = arm-elf-strip -O binary -o
CFLAGS = -mapcs -fomit-frame-pointer -O1 -c
ASFLAGS =

OBJS = start.o \
undef.o \
swi.o \
swiapi.o \
prefetch.o \
data.o \
reserved.o \
irq.o \
fiq.o \
scheduler.o \
mmu.o \
util.o \
async.o \
swi_handler.o \
bringup.o \
cpsr.o \
irq_handler.o \
events_init.o \
tick_service.o \
ddf_io.o \
led_driver.o \
serial_driver.o \
cinit.o \
uid.o \
jump.o \
init.o \
mmupcb.o \
sal.o

all : ${OBJS}
	${LINKER} -o ../image/mmuslos.elf linker.dat
	${CONVERT} ../image/mmuslos.bin -s ../image/mmuslos.elf

start.o : ../src/start.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
init.o : ../src/cm920iap/init.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
mmupcb.o : ../src/cm920iap/mmupcb.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
undef.o : ../src/undef.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
mmu.o : ../src/memory/mmu.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
async.o : ../src/memory/async.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<

swi.o : ../src/swi.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
sal.o : ../src/sal.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<

jump.o : ../src/core/jump.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<

prefetch.o : ../src/prefetch.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
data.o : ../src/data.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
reserved.o : ../src/reserved.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
irq.o : ../src/irq.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
fiq.o : ../src/fiq.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
scheduler.o : ../src/scheduler.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
irq_handler.o : ../src/cm920iap/events/irq_handler.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
bringup.o : ../src/events/bringup.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
cpsr.o : ../src/events/cpsr.s
	${ASSEMBLER} ${ASFLAGS} -o $@ $<
 
events_init.o : ../src/cm920iap/events/events_init.c
	${CC} ${CFLAGS} -o $@ $<
 
swiapi.o : ../src/core/swiapi.c
	${CC} ${CFLAGS} -o $@ $<

util.o : ../src/memory/util.c
	${CC} ${CFLAGS} -o $@ $<

swi_handler.o : ../src/cm920iap/events/swi_handler.c
	${CC} ${CFLAGS} -O1 -c -o $@ $<

tick_service.o : ../src/cm920iap/events/tick_service.c
	${CC} ${CFLAGS} -o $@ $<
 
ddf_io.o : ../src/devices/ddf_io.c
	${CC} ${CFLAGS} -o $@ $<
 
led_driver.o : ../src/cm920iap/devices/led_driver.c
	${CC} ${CFLAGS} -o $@ $<
 
serial_driver.o : ../src/cm920iap/devices/serial_driver.c
	${CC} ${CFLAGS} -o $@ $<
   
cinit.o : ../src/core/cinit.c
	${CC} ${CFLAGS} -o $@ $<
 
uid.o : ../src/core/uid.c
	${CC} ${CFLAGS} -o $@ $<
 