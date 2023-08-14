CC=arm-none-eabi-gcc
CPU=cortex-m3
CFLAGS=-mcpu=$(CPU) -mthumb -Wall -g3 -std=gnu11 -O0
TARGET=firmware
LDFLAGS=-g -nostdlib -Tstm32f103c8t6.ld -Wl,-Map=$(TARGET).map
OBJ=startup.o main.o rcc.o gpio.o syst.o

.PHONY: all clean flash debugger clean

all:$(TARGET).bin $(TARGET).objdump

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
debugger: $(TARGET).elf
	openocd -f openocd.cfg
clean:
	rm -f *.o firmware{,.{bin,elf,map,objdump}}

