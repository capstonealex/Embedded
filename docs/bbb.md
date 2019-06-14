## Editing BBB default sudo and root passwords

Username: debian

Password (also for sudo): temppwd

Root password: root

---

# Connect to BBB through VM

## Setting up BBB outside VM (To be done first)

1. Fully shutdown VirtualBox and plug the BBB in to the host computer's USB. It should show up as a USB drive.
2. Install the correct BBB drivers for your host OS. These can be obtained from the http://beagleboard.org/getting-started. Note: The drivers stored in the BBB that shows up as USB device (on your computer) maybe outdated.
   - If the drivers were installed correctly, you should be able to remote login to the BBB (root@192.168.7.2 or debian@192.168.7.2 with password: temppwd) using Putty (Win) or SSH (linux/mac).

---

## Setting up VirtualBox to enable USB ethernet connection to BBB.

1. Download and install the VirtualBox Oracle VM VirtualBox [Extension Pack](https://www.virtualbox.org/wiki/Downloads).
2. Under VirtualBox Settings > Network > Adapter, Enable Network Adapter and select NAT. Now launch the VM and check that you have internet access.
   - Shutdown the VM.
   - In VirtualBox go to settings > ports > usb. For windows this will be settings > USB
   - Select USB 3.0 (xHCI) Controller, or USB 2.0 if you are using a 2.0 port on your computer.
   - Select "add new USB filter" and select the BBB (you may need to connect the BBB for it to show up in the list). Keep default settings and make sure that the new filter is ticked.
   - Safely eject and Physically disconnect the BBB from your computer
3. Start the VM and connect the BBB to the USB port. After a small delay, the BBB should show up in the guest OS.
   - Switch the internet connection to USB ethernet in the guest OS. In Debian this can be done through Settings > Network > USB Ethernet, toggle ON button.
4. SSH into BBB using `ssh root@192.168.7.2` or debian@192.168.7.2 with password: temppwd
   - Note: To get internet access on the guest OS, you would need to switch back to wired ethernet in Debian network settings.
   - To end session issue: `ctrl+d`

---
## Checking current OS/kernel version
Use one of the following. They give different level of details.
* `cat /etc/os-release`
* `lsb_release -a`
* `hostnamectl`
* `uname -r` to get just kernel

## Getting and flashing BBB images
1. Get latest image from https://beagleboard.org/latest-images. The regular version has a GUI while the IOT version does not.
2. Use [etcher](https://www.balena.io/etcher/) to install the image onto an SD card (4GB or greater). If using an alternate tool like UNetbootin, you may have to first extract the image.
3. You can now either live boot of the SD card or flash the image onto the beagle bone.

### Live booting from SD card
1. Power off the BBB and insert the SD card. 
1. While pressing the boot button on the BBB (near the SD card), power it up. Pressing the boot button may not be required with the BBB we are using.
1. The BBB will start up and boot the OS off the SD card. You can verify this by running `lsblk`. This shows all the partitions (internal and external). It shows a forward slash next to the boot partition. The SD card should be mmcblk0 and internal emmc should be mmcblk1. Livebooting will show a / next to the SD card partition and regular booting will show it next to the internal emmc partition.

### Flashing the image
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
* https://beagleboard.org/getting-started#update
* https://elinux.org/Beagleboard:BeagleBoneBlack_Debian

---