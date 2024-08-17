## connect to openocd server
define reconnect
  target remote localhost:3333
end

## Restart device and reload symbols
define reload
  monitor reset halt
  load
  monitor reset init
  continue
end

## flash elf to device
define flash
  monitor reset init
  monitor flash write_image erase /home/rhys/ertos/firmware.elf
  monitor reset halt
end

## close openocd service when exiting
define hook-quit
  make stop-openocd
  set confirm off
end

make start-openocd
file firmware.elf
reconnect
flash
break main
continue

