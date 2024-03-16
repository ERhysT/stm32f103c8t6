CC=arm-none-eabi-gcc
CPU=cortex-m3
CFLAGS=-mcpu=$(CPU) -mthumb -Wall -g3 -std=gnu11 -O0
TARGET=firmware
LDFLAGS=-g -mcpu=$(CPU) -mthumb --specs=nano.specs -Tstm32f103c8t6.ld -Wl,-Map=$(TARGET).map
OBJ=startup.o main.o rcc.o gpio.o syst.o usart.o syscalls.o

# -nostartfiles

.PHONY: all clean flash start-openocd stop-openocd clean test tags

all: tags $(TARGET).bin $(TARGET).objdump 

$(TARGET).bin: $(TARGET).elf
	arm-none-eabi-objcopy -O binary $< $@
$(TARGET).objdump: $(TARGET).elf
	arm-none-eabi-objdump -h $< | tee $@
$(TARGET).elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^
%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

flash: $(TARGET).bin
	st-flash --reset write $(TARGET).bin 0x80000000

start-openocd: $(TARGET).elf
	systemctl --user start stm32f103c8t6_openocd.service
stop-openocd:
	systemctl --user stop stm32f103c8t6_openocd.service
screen:
	sudo screen /dev/ttyUSB0 9600 8N1
clean:
	rm -f *.o firmware{,.{bin,elf,map,objdump}}
test:
	make -C test/
tags:
	etags *.c *.h
