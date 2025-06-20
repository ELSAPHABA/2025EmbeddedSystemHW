all: textlcdtest.elf

textlcdtest.elf: libMyPeri.a textlcdtest.o
	arm-linux-gnueabi-gcc textlcdtest.o -l MyPeri -L. -o textlcdtest.elf
	echo "		5) textlcdtest.elf"

textlcdtest.o: textlcdtest.c
	arm-linux-gnueabi-gcc -c -o textlcdtest.o textlcdtest.c
	echo "		4) textlcdtest.o"

libMyPeri.a: textlcd.o
	arm-linux-gnueabi-ar rc libMyPeri.a textlcd.o
	echo "		3) libMyPeri.a"

textlcd.o: textlcd.c textlcd.h
	arm-linux-gnueabi-gcc --static -c -o textlcd.o textlcd.c
	echo "		2) textlcd.o"

clear : 
	rm *.o
	rm libMyPeri.a
	echo "		1) make start"
	make