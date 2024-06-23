#!/bin/bash

source build.config
source .config

cat <<EOF >> boot/grub/grub.cfg
loadfont unicode
source /boot/grub/config.cfg
set timeout=5

set gfxmode=auto
insmod all_video
insmod gfxterm
insmod png

set theme=/boot/grub/lingmo/theme.txt

set color_normal=white/black
set color_highlight=black/light-gray

menuentry "Start ${SYSTEM_NAME} ${SYSTEM_VERSION}" --class lingmo {
        set gfxpayload=keep
        linux   /live/vmlinuz-${kERNEL_VERSION}-${SYSTEM_ARCH} boot=live username=lingmo noautologin quiet splash findiso=${iso_path} ---
        initrd /live/initrd.img-${KERNEL_VERSION}-${SYSTEM_ARCH}
}
menuentry "Start ${SYSTEM_NAME} ${SYSTEM_VERSION} (compatibility mode)" --class lingmo {
        set gfxpayload=keep
        linux   /live/vmlinuz-${kERNEL_VERSION}-${SYSTEM_ARCH} boot=live username=lingmo noautologin quiet splash findiso=${iso_path} nomodeset ---
        initrd /live/initrd.img-${kERNEL_VERSION}-${SYSTEM_ARCH}
}
menuentry "Alternate graphical installer" {
        linux /install/gtk/vmlinuz vga=788  --- quiet custom options here
        initrd /install/gtk/initrd.gz
}
menuentry "Alternate textual installer" {
        linux /install/vmlinuz vga=normal  --- quiet custom options here
        initrd /install/initrd.gz
}
grub_platform

if [ "$grub_platform" = "efi" ]; then
menuentry 'Boot from next volume' {
        exit 1
}
menuentry 'UEFI Firmware Settings' {
        fwsetup
}
menuentry 'Memory test' {
	linux   /live/memtest.bin                                                       
}
fi
EOF
