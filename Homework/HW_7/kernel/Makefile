obj-m += systimer.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell unamr -r)/build M=$(PWD) clean

