define reconnect
    target remote localhost:3333
end

define reload
    mon reset halt
    make
    load
    mon reset init
    continue
end

define flash
  monitor reset init
  monitor flash write_image erase /home/rhys/bluepill/firmware.elf
  monitor reset halt
end

make all
file firmware.elf
reconnect
flash
# break main			
break usart_setup
continue
print baudtobrr(9600, 8000000)
print (52<<4)|1

print baudtobrr(9600, 36000000)
print (234<<4)|6

print baudtobrr(115200, 36000000)
print (19<<4)|8

# print baudtobrr(2250000, 36000000)
