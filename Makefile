
#******************************************************************************
CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump

#******************************************************************************

EXECNAME = lp_base

BOARD = ek-lm4f120xl
STELLARIS_ROOT = /embedded/StellarisWare

INCLUDES += -Isrc
INCLUDES += -I$(STELLARIS_ROOT)
INCLUDES += -I$(STELLARIS_ROOT)/utils
INCLUDES += -I$(STELLARIS_ROOT)/boards/$(BOARD)

# VPATH = . src
VPATH += $(STELLARIS_ROOT)/utils
VPATH += $(STELLARIS_ROOT)/boards/$(BOARD)/drivers

SOURCE = src/main.c
SOURCE += src/startup.c
SOURCE += $(STELLARIS_ROOT)/driverlib/adc.c
SOURCE += $(STELLARIS_ROOT)/driverlib/can.c
SOURCE += $(STELLARIS_ROOT)/driverlib/comp.c
SOURCE += $(STELLARIS_ROOT)/driverlib/cpu.c
SOURCE += $(STELLARIS_ROOT)/driverlib/eeprom.c
SOURCE += $(STELLARIS_ROOT)/driverlib/epi.c
SOURCE += $(STELLARIS_ROOT)/driverlib/ethernet.c
SOURCE += $(STELLARIS_ROOT)/driverlib/fan.c
SOURCE += $(STELLARIS_ROOT)/driverlib/flash.c
SOURCE += $(STELLARIS_ROOT)/driverlib/fpu.c
SOURCE += $(STELLARIS_ROOT)/driverlib/gpio.c
SOURCE += $(STELLARIS_ROOT)/driverlib/hibernate.c
SOURCE += $(STELLARIS_ROOT)/driverlib/i2c.c
SOURCE += $(STELLARIS_ROOT)/driverlib/i2s.c
SOURCE += $(STELLARIS_ROOT)/driverlib/interrupt.c
SOURCE += $(STELLARIS_ROOT)/driverlib/lpc.c
SOURCE += $(STELLARIS_ROOT)/driverlib/mpu.c
SOURCE += $(STELLARIS_ROOT)/driverlib/peci.c
SOURCE += $(STELLARIS_ROOT)/driverlib/pwm.c
SOURCE += $(STELLARIS_ROOT)/driverlib/qei.c
SOURCE += $(STELLARIS_ROOT)/driverlib/ssi.c
SOURCE += $(STELLARIS_ROOT)/driverlib/sysctl.c
SOURCE += $(STELLARIS_ROOT)/driverlib/sysexc.c
SOURCE += $(STELLARIS_ROOT)/driverlib/systick.c
SOURCE += $(STELLARIS_ROOT)/driverlib/timer.c
SOURCE += $(STELLARIS_ROOT)/driverlib/uart.c
SOURCE += $(STELLARIS_ROOT)/driverlib/udma.c
SOURCE += $(STELLARIS_ROOT)/driverlib/usb.c
SOURCE += $(STELLARIS_ROOT)/driverlib/watchdog.c


#******************************************************************************

PART = LM4F120H5QR
CORE = cortex-m4

DEFINES = -Dgcc -DPART_$(PART) -DTARGET_IS_BLIZZARD_RA1
DEFINES += -DSTACK_SIZE=256

AFLAGS = -mthumb -mcpu=$(CORE) $(INCLUDES)
CFLAGS = -mthumb -mcpu=$(CORE) -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -std=gnu99 -Wall -Wno-unused -g -Os
CFLAGS += $(DEFINES) $(INCLUDES)

LIBS = -lm -lc -lnosys 

LDFLAGS = -mthumb -mcpu=$(CORE)
LDFLAGS += -nodefaultlibs -nostartfiles
LDFLAGS += -Wl,-Map,$(EXECNAME).map
LDFLAGS += -Wl,--gc-sections
LDSCRIPT = lm4f120.ld

#******************************************************************************
# Generate lists of object and dependency files
#******************************************************************************
CSOURCES = $(filter %.c,$(SOURCE))
CPPSOURCES = $(filter %.cpp,$(SOURCE))
ASMSOURCES = $(filter %.s,$(SOURCE))

OBJECTS = $(addprefix obj/, $(CSOURCES:.c=.c.o)) \
          $(addprefix obj/, $(CPPSOURCES:.cpp=.cpp.o)) \
          $(addprefix obj/, $(ASMSOURCES:.s=.s.o))

DISASM = $(addprefix disasm/, $(CSOURCES:.c=.c.s)) \
          $(addprefix disasm/, $(CPPSOURCES:.cpp=.cpp.s)) \
          $(addprefix disasm/, $(ASMSOURCES:.s=.s.s))

# DEPENDFILES = $(OBJECTS:.o=.d)

LIBGCC = $(shell $(CC) $(CFLAGS) -print-libgcc-file-name)
LIBC = $(shell $(CC) $(CFLAGS) -print-file-name=libc.a)

# Non-working attempt at OpenOCD programming with an external programmer
#OOCD_CFG = -f interface/olimex-arm-usb-ocd.cfg -f ek-lm4f120xl.cfg
#OOCD_RESET = -c 'reset'
#OOCD_RESET_HALT = -c 'reset halt'
#OOCD_FLASH = -c 'flash write_image erase obj/$(EXECNAME).bin'

#******************************************************************************
# Dependency rules
#******************************************************************************

.PHONY: all default clean depend echo none disasm

default: $(EXECNAME).elf Makefile

install:

clean:
	rm -rf obj
	rm -rf deps
	rm -f $(EXECNAME).elf
	rm -f $(EXECNAME).bin
	rm -f $(EXECNAME).map


$(EXECNAME).elf: $(OBJECTS)
	$(LD) -T $(LDSCRIPT) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS) '$(LIBC)' '$(LIBGCC)'


disasm: $(DISASM)
	$(OD) -d $(EXECNAME).elf >disasm/$(EXECNAME).s

flash: $(EXECNAME).elf
	$(CP) -O binary $(EXECNAME).elf $(EXECNAME).bin
	/embedded/lm4tools/lm4flash $(EXECNAME).bin
	#openocd ${OOCD_CFG} -c 'init' ${OOCD_RESET_HALT} ${OOCD_FLASH} ${OOCD_RESET} -c 'shutdown'

obj/%.c.o: %.c
	$(shell if [ ! -d $(addprefix obj/, $(dir $<)) ]; then mkdir -p $(addprefix obj/, $(dir $<)); fi )
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.cpp.o: %.cpp
	$(shell if [ ! -d $(addprefix obj/, $(dir $<)) ]; then mkdir -p $(addprefix obj/, $(dir $<)); fi )
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.s.o: %.s
	$(shell if [ ! -d $(addprefix obj/, $(dir $<)) ]; then mkdir -p $(addprefix obj/, $(dir $<)); fi )
	$(CC) $(CFLAGS) -c $< -o $@


disasm/%.c.s: %.c
	$(shell if [ ! -d $(addprefix disasm/, $(dir $<)) ]; then mkdir -p $(addprefix disasm/, $(dir $<)); fi )
	$(CC) $(CFLAGS) -S $< -o $@

disasm/%.cpp.s: %.cpp
	$(shell if [ ! -d $(addprefix disasm/, $(dir $<)) ]; then mkdir -p $(addprefix disasm/, $(dir $<)); fi )
	$(CC) $(CFLAGS) -S $< -o $@

disasm/%.s.s: %.s
	$(shell if [ ! -d $(addprefix disasm/, $(dir $<)) ]; then mkdir -p $(addprefix disasm/, $(dir $<)); fi )
	$(CC) $(CFLAGS) -S $< -o $@

#******************************************************************************
# Dependency-generating rules
#******************************************************************************

ifneq ($(MAKECMDGOALS),clean)
-include $(addprefix deps/, $(subst .c,.c.d,$(CSOURCES)))
-include $(addprefix deps/, $(subst .cpp,.cpp.d,$(CPPSOURCES)))
-include $(addprefix deps/, $(subst .s,.s.d,$(ASMSOURCES)))
endif

deps/%.c.d: %.c
	$(shell if [ ! -d $(addprefix deps/, $(dir $<)) ]; then mkdir -p $(addprefix deps/, $(dir $<)); fi )
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

deps/%.cpp.d: %.cpp
	$(shell if [ ! -d $(addprefix deps/, $(dir $<)) ]; then mkdir -p $(addprefix deps/, $(dir $<)); fi )
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

deps/%.s.d: %.s
	$(shell if [ ! -d $(addprefix deps/, $(dir $<)) ]; then mkdir -p $(addprefix deps/, $(dir $<)); fi )
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

#******************************************************************************
# End of file
#******************************************************************************
