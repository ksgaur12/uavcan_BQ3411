#!/bin/bash

ref_v=$(git show -s --format=%h)

echo 'Compiling bootloader for STM32F3 with' $ref_v

bl_dir='bootloader'

cd $bl_dir

BOARD=com.cdspace.asu make || exit 1

echo '******************************************************'
echo '	BOOTLOADER BUILD SUCCESS!				'
echo '******************************************************'

elf_d='bootloader/build/com.cdspace.asu_bl/bin/main.elf'

cd ../

openocd -f openocd.cfg -c "program $elf_d verify reset exit" || exit 1

echo '******************************************************'
echo '	BOOTLOADER DLASH SUCCESS!				'
echo '******************************************************'




