all: buttontest.elf

buttontest.elf: libMyPeri.a buttontest.o
	arm-linux-gnueabi-gcc buttontest.o -l MyPeri -L. -o buttontest.elf -lpthread
	echo "		5) buttontest.elf"

buttontest.o: buttontest.c button.h
	arm-linux-gnueabi-gcc -c -o buttontest.o buttontest.c
	echo "		4) buttontest.o"

libMyPeri.a: button.o
	arm-linux-gnueabi-ar rc libMyPeri.a button.o
	echo "		3) libMyPeri.a"

button.o: button.c button.h
	arm-linux-gnueabi-gcc --static -c -o button.o button.c
	echo "		2) button.o"

clear :
	rm -f *.o
	rm -f libMyPeri.a
	echo "		1) make start"
	make
