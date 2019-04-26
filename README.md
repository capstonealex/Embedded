# Embeded


## Hardware
* BeagleBone black
* Mac or windows computer (Mac prefered)

## Software
### Local
* Linux OS: [Debian Stretch](https://www.debian.org/releases/stretch/)(
* Virtual Environment: [Virtual Box](https://www.virtualbox.org/)
* Eclipse IDE: 

## Create Local Desktop workbench
1. Install virtual box on a local machine and make an instance of Debian 9.8
    *  Download virtual box: [Virtual box](www.virtualbox.org)
    *  Make a new virtual machine for a Linux Debian distribution with Memory settings:
    *  Make sure to give enough video memory(~70mb)
    *  Download Debian 9.8 netinst CD image for amd64 and mount for a virtual machine.
    *  To mount follow these steps.
            * From the VBOX details window of your created Virtual Machine click the settings icon.
            * Under the storage icon, you should see Controller: IDE in the left side of the screen. Click on the Empty disk below it.
            * Attributes -> Optical drive: click the disk icon: Chose Virtual Optical Disk -> select the 9.8 netinst CD image.
            *Click Ok
    * Click Start and follow Debian install instructions, use any GUI you wish, this project follows a GNOME installation.

    * Once installed reboot and make sure the system boots, if you see a "No boot device" eject the install disk and try again.

2. Enable Debian utilities for development.
* Guest additions.
* On the Virtual box menu Choose “Devices”->”Insert Guest Additions CD image…”
    * If this does not automatically run then follow the below code.

```linux
user@debian:~$ su -
root@debian:~# apt-get update
root@debian:~# apt-get install build-essential module-assistant
root@debian:~# m-a prepare
root@debian:~# cd /media/cdrom
root@debian:~# sh ./VBoxLinuxAdditions.run
root@debian:~# reboot
```
* Enable sudo
```linux
user@debian:~$ su -
root@debian:~# apt-get install sudo
root@debian:~# visudo
--> Under visduo -> User priveledge specifications 
-> add your user as:_your_username ALL=(ALL:ALL) ALL
```
## Setting up cross-compilation tool chain
1. Using cross-toolchain repository install armhf package
   ```apt-cache search cross-build-essential
      sudo apt install crossbuild-essential-armhf
   ``` 
2. Test installation by calling it directly: `arm-linux-gnueabihf-g++ -v`
* Return should be: ```“COLLECT_GCC=arm-linux-gnueabihf-g++ …
Thread model: posix
gcc version 6.3.0 20170516 (Debian 6.3.0-18) ”```
3. Emulate armhf architecture with QEMU
* `sudo apt install qemu-user-static`
* Notify dpkg (package management system) that multiple architecture packages will be on the machine.
```linux
user@desktop:~$ sudo dpkg --add-architecture armhf
user@desktop:~$ dpkg --print-foreign-architectures
armhf ”
```
* Check for success with: `user@desktop:~$ sudo apt update`
* Return should have several packages ending in `armhf Packages` if not try again.

4. Test toolchain compiles and runs under emulator.
* `nano testcross.cpp`
```cpp
#include <iostream>
using namespace std;

int main() 
{
    cout << "Hello, From amrhf architecture!";
    return 0;
}
```
* Save the file to the desktop
* Attempt to compile with -static to statically build the executable.
```linux
user@desktop:~$ arm-linux-gnuabihf-g++ -static testcross.cpp -o testcross
user@desktop:~$ ./testcross
```
* Return should print:`Hello, From amrhf architecture!`
5. Set up Multiarch cross-compliation with third-party libraries
*


## Install development software (Eclipse) and configure for cross-compilation.
1. Install a web browser such as chrome
*
2. Download Eclipse Version (####)
3. Con


To launch Eclipse:'./eclipse &' *Note:you must be in the elipse directory (cd /ECLIPSE_PATH) before running the launch command

## Configure Eclipse for Remote access (RSE)
1. 


## Set up remote debugging.
1.


## Connecting to the BBB through the Virtual Machine (VM)
### Setting up BBB outside VM (To be done first).
* Fully shutdown VirtualBox and plug the BBB in to the host computer's USB. It should show up as a USB drive. 
* Install the correct BBB drivers for your host OS. These can be obtained from the http://beagleboard.org/getting-started. Note: The drivers stored in the BBB USB drive maybe outdated. 
* If the drivers were installed correctly, you should be able to remote login to the BBB (root@192.168.7.2) using Putty (Win) or SSH (linux/mac).
### Setting up VirtualBox to enable USB ethernet connection to BBB.
* Download and install the VirtualBox Oracle VM VirtualBox Extension Pack (https://www.virtualbox.org/wiki/Downloads)
* Under VirtualBox Settings > Network > Adapter, Enable Network Adapter and select NAT. Now launch the VM and check that you have internet access.  
* Shutdown the VM. 
* In VirtualBox go to settings > ports > usb. For windows this will be settings > USB
* Select USB 3.0 (xHCI) Controller, or USB 2.0 if you are using a  2.0 port on your computer. 
* Select "add new USB filter" and select the BBB (you may need to connect the BBB for it to show up in the list). Keep default settings and make sure that the new filter is ticked.
* Physically disconnect the BBB from your computer
* Start the VM and connect the BBB to the USB port. After a small delay, the BBB should show up in the guest OS. 
* The network adapter should be changed to USB ethernet in the guest OS. In Debian this can done through Settings > Network > USB Ethernet, toggle ON button. 
* You should now be able to SSH into BBB using `ssh root@192.168.7.2`
* Note: To get internet access on the guest OS, you need to switch back to wired ethernet in Debian network settings. 

## Connecting BBB to WiFi
Not all versions of BBB have a WiFi module.

* Run `connmanctl technologies` on the BBB root to see current wireless status.
* `sudo connmanctl`
* `enable wifi`
* `scan wifi` You should get a scan complete message. If there is an error run `tether wifi disable`
* `services`
* `agent on`
* `connect <wifiname>`
* `config <wifiname> --ipv4 manual <BBB wifi IP> 255.255.255.0 <router IP> --nameservers 8.8.8.8`
* `quit`
* Note that the BBB Wifi IP should belong to the Wifi subnet and is different from 192.168.7.2 that is used to connect to BBB over USB. 

## Cross compiling on the BBB

## Eclipse cross compilation and Remote System Explorer (RSE)
