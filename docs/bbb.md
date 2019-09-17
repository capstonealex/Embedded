
# BBB Developer

This page contains information about flashing the BBB with a Linux Distro and changing kernels.

## Checking current OS/kernel version in BBB
Use one of the following in terminal. They give different level of details.

* `cat /etc/os-release`
* `lsb_release -a`
* `hostnamectl`
* `uname -r` to get just kernel

## Getting and flashing BBB images
The instructions below are specifically for the official images (containing Debian Stretch) from the BBB website. But you can follow similar steps for any compatible images. 

1. Get latest image from [https://beagleboard.org/latest-images](https://beagleboard.org/latest-images). The regular version has a GUI while the IOT version does not.
2. Use [etcher](https://www.balena.io/etcher/) to install the image onto an SD card (4GB or greater). If using an alternate tool like UNetbootin, you may have to first extract the image.
3. You can now either live boot of the SD card or flash the image onto the beagle bone.

## Live booting from SD card

1. Power off the BBB and insert the SD card with OS image. 
1. While pressing the boot button on the BBB (near the SD card), power it up. Pressing the boot button may not be required with the BBB we are using.
1. The BBB will start up and boot the OS off the SD card. You can verify this by running `lsblk`. This shows all the partitions (internal and external). It shows a forward slash next to the boot partition. The SD card should be `mmcblk0` and internal emmc should be `mmcblk1`. Livebooting will show a `/` next to the SD card partition and regular booting will show it next to the internal emmc partition.

## Flashing the image

1. In order to make the SD card image flashable, we need to modify the `uEnv.txt` file. This can be done either on the BBB or the host PC. Below instructions are for the BBB. 
1. First, live boot using the SD card.
2. Open `/boot/uEnv.txt`, you may need sudo to edit the file. 
3. At the bottom of the file, uncomment the line (remove #): `cmdline=init=/opt/scripts/tools/eMMC/init-eMMC-flasher-v3.sh`
4. Save file and reboot BBB. You may need to press the boot button. The beagle bone will flash the image on the SD card. This can seen by the LED light cylon pattern.
5. NOTE: Anytime this SD card is inserted while starting up BBB, it will flash the BBB. So remember to remove the SD card once done.

## Additional information
* Editing the `uEnv.txt` file (to make it flashable) does not need to done from the BBB. You can just access the SD card on the host computer and edit it there as well. 
* The newer BBB images do not come with root password disabled. The default sudo password is `temppwd` and root password is `root`. Default username is `debian`.
* Is using linux, the SSH may throw an authentication error after flashing new images/livebooting. To fix this, you have to clear the currently authorised key: `ssh-keygen -R 192.168.7.2`

## Sources
* [https://beagleboard.org/getting-started#update](https://beagleboard.org/getting-started#update)
* [https://elinux.org/Beagleboard:BeagleBoneBlack_Debian](https://elinux.org/Beagleboard:BeagleBoneBlack_Debian)
