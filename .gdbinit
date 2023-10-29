define reconnect
  target remote localhost:3333
end

define reload
  monitor reset halt
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

