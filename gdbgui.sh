#!/bin/bash

. /media/anna/552cabe3-d5d7-4cd6-b828-2c0fefc4f84f/esp-idf/esp-idf/export.sh
gdbgui -g riscv32-esp-elf-gdb --gdb-args="-x=${PWD}/gdbinit"

# gdbgui --gdb-cmd="/home/anna/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch3-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gdb -x=/media/anna/Daten2/Development/SlimeVR/SlimeVR-Tracker-ESP2/gdbinit"
