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
  monitor flash write_image erase firmware.elf
  monitor reset halt
end

file firmware.elf
reconnect
flash

