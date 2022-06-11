file .pio/build/esp32c3/firmware.elf
target extended-remote :3333
set remote hardware-watchpoint-limit 2
mon reset halt
flushregs
thb main
c
