LZMA=lzma
MV=mv

MKIMG=mkimg_mips
CP=cp
rm -rf ./binary

mv rabi_ota.map ./release/
mv ./${1} ./release/
cd ./release/
ANCHOR=../../../../../../../other/anchor/bin/anchor.exe

mipsel-linux-objcopy -O binary ${1} rabi.bin
$ANCHOR -p rabi_ota.bin rabi.bin
rm -f rabi.bin
mipsel-linux-objdump -d rabi_ota.elf > rabi_ota.s
$ANCHOR -i rabi_ota.img rabi_ota.bin 0x80008000 0x80008000

  cp rabi_ota.bin rabi_ota.tmp
	rm -f rabi_ota.tmp.lzma
	lzma -z -k rabi_ota.tmp
	$MKIMG rabi_ota.tmp.lzma rabi_ota_lzma.img -g
	rm -f rabi_ota.tmp.lzma

echo "post build process completes"