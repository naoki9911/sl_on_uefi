BOOT_LOADER = build/DEBUG_GCC5/X64/sl_on_uefi/sl_uefi/DEBUG/sl_uefi.efi
BOOT_IMAGE_PATH = image/EFI/BOOT
run:
	cp -r $(BOOT_LOADER) $(BOOT_IMAGE_PATH)/BOOTX64.efi
	qemu-system-x86_64 \
	-drive if=pflash,format=raw,readonly,file=OVMF_CODE.fd \
	-drive if=pflash,format=raw,file=OVMF_VARS.fd \
	-drive if=ide,file=fat:rw:image,index=0,media=disk \
	-gdb tcp::4321 \
	-m 2048 \
	-smp 2 \
	-monitor stdio \

