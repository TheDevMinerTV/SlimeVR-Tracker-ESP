#!/bin/bash

../openocd-esp32/src/openocd -s ../openocd-esp32/tcl -f board/esp32c3-builtin.cfg -c "program_esp .pio/build/esp32c3/firmware.bin 0x10000 verify exit"
