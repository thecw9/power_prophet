#!/bin/sh
if [ $(getconf WORD_BIT) = '32' ] && [ $(getconf LONG_BIT) = '64' ] ; then
    sudo insmod ./c/drv64/acts3100.ko
	cp ./c/drv64/libacts3100.so ./c/lib/libacts3100.so
	echo "install 64bit lib success"
else    
    sudo insmod ./c/drv32/acts3100.ko
	cp ./c/drv32/libacts3100.so ./c/lib/libacts3100.so
	echo "install 32bit lib success"
fi

mydev="/dev/acts3100-0"
if [ -c "$mydev"* ];then
	if [ ! -r "$mydev"* ];then
		sudo chmod 666 "$mydev"*
	fi
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./c/lib
else
	echo "The Device "$mydev"* not exist!"
fi

