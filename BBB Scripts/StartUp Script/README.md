# Making a startup script for CAN1 interface on BBB
1.	Create a script file (say setupCANinterface.sh) and put it in /usr/bin/

	```
	#!/bin/bash

	#initialisation CAN interface

	#setting up CAN1 interface on BBB.
	sudo config-pin p9.24 can
	sudo config-pin p9.26 can
	sudo ip link set can1 up type can bitrate 1000000 &
	sudo ifconfig can1 up &
	
	cd /home/debian/CANopenSocket/canopend

	echo - > od4_storage &
	echo - > od4_storage_auto &
	```
	
2.	Make the script runnable using `sudo chmod a+x setupCANinterface.sh`
3.	Don’t put anything is script that is blocking. 
4.	Now `sudo nano /etc/rc.local`
5.	Add 

	```
	#!/bin/sh -e
	/usr/bin/yourscript.sh
	exit 0
	```
	
6.	Make rc.local runnable using `sudo chmod a+x rc.local`
7.	Subsequently, just modify `yourscript.sh` to whatever you need. Can also start programs this same way.


Read more here
https://askubuntu.com/questions/9853/how-can-i-make-rc-local-run-on-startup

# Running multiple programs

```
#!/bin/sh -e
/usr/bin/pintest3.sh
/usr/bin/pintest.out &
/usr/bin/pintest4.sh
/usr/bin/pintest2.out
/usr/bin/pintest5.sh
exit 0
```

Consider above rc.local. pintest3.sh blocks. It has to complete before pintest.out runs. pintest.out is run in background since we are using `&`

