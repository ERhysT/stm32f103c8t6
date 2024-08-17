ERTOS stm32f103c8t6 "bluepill" baremetal testing

Functions:
* Blinks LED on PC13
* Mirrors UART RX back to TX

Software used: gcc, gdb, GNU make, GNU screen and openocd.

Connections:
* ST-LINK V2 -> onboard debugger
* bluepill A2 -> UART RXD
* bluepill A3 -> UART TXD

## Set up the debugger

For OpenOCD / STLINK-V2 debugging there is a systemd service file
provided `stm32f103c8t6_openocd.service`. The service starts and stops
the openocd debugger. Open the service file and correct the path to
`openocd.cfg` which contains the st-link interface configuration for
the bluepill. The connection can be manually controlled and monitored
using the commands below. If using gdb, the provided init file
will handle the debugger connections so you dont need to do this.

```
systemctl --user start stm32f103c8t6_openocd.service
systemctl --user status stm32f103c8t6_openocd.service
systemctl --user stop stm32f103c8t6_openocd.service
```

## UART interface

The UART characters input to the device are mirrored back out for
testing. To send and recive characters over UART first get the usb
device name, normally something like `/dev/ttyUSB0` and then start GNU
screen. Use `C-a ?` to get screen keybinds and `C-a k` to quit screen.

```
sudo screen /dev/ttyUSB0 9600 8N1
```

## Compiling

To generate an .bin, .elf and generate an objdump use `make all`.

## Flashing

Flashing the device is done through gdb. A gdb init file is provided
`.gdbinit`. Check any absolute paths in this file. On opening gdb,
openocd will connect to the debugger, generate an up-to-date elf file,
flash it, insert a breakpoint at main and run the program.

On exiting gdb the connection to the debugger is closed automatically.








