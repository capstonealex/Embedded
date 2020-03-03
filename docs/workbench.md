# Workbench
## Version 2.0 : Using Docker Container (tested mac OSX and ubuntu)
### Docker container cross
1. Install Docker and Docker hub[Docker Desktop for Mac and Windows | Docker](https://www.docker.com/products/docker-desktop)
2. docker pull alejandro4siana/cross-bbb-debian
3. cd into the file you wish to cross compile in (e.g. ALEX)
```
docker run siana/cross-bbb-debian > bbbxc
chmod +x bbbxc
```
4. run command `./bbbxc make	` which should create your executable ready to upload on BBB
5.(OPTIONAL) Install vscode and use docker container as compiling environment:[VS code](https://code.visualstudio.com/docs/remote/containers)
## Windows Virtual GDB Beagle bone.
PreBuilt GNU Windows toolchain for beagle bone and accompanying plugin for Visual Studio: [Link](https://gnutoolchains.com/beaglebone/)

## Virtual Box with instance of Debian 9.8

- Download virtual box: [Virtual box](www.virtualbox.org)
- Make a new virtual machine for a Linux Debian distribution.
- Make sure to give enough video memory(~70mb)
- [Download Debian](https://www.debian.org/distrib/) 9.8 netinst CD image for amd64 and mount for a virtual machine.
- To mount debain disk follow these steps.
  - From the VBOX details window of your created Virtual Machine click the settings icon.
  - Under the storage icon, you should see Controller: IDE in the left side of the screen. Click on the Empty disk below it.
  - Attributes -> Optical drive: click the disk icon: Chose Virtual Optical Disk -> select the 9.8 netinst CD image.
  - Click Ok
- Click Start and follow Debian install instructions, use any GUI you wish, this project follows a GNOME installation.
- Once installed reboot and make sure the system boots, if you see a "No boot device" eject the install disk and try again.


## Enable Debian utilities for development.

- Guest additions.
- On the Virtual box menu Choose “Devices”->”Insert Guest Additions CD image…”
- If this does not automatically run then follow the below code.

```linux
user@debian:~$ su -
root@debian:~# apt-get update
root@debian:~# apt-get install build-essential module-assistant
root@debian:~# m-a prepare
root@debian:~# cd /media/cdrom
root@debian:~# sh ./VBoxLinuxAdditions.run
root@debian:~# reboot
```

## Enable sudo

```linux
user@debian:~$ su -
root@debian:~# apt-get install sudo
root@debian:~# visudo
--> Under visduo -> User priveledge specifications
-> add your user as:_your_username ALL=(ALL:ALL) ALL
```

# Virtual Box UX improvements

## Enabling clipboard b/w host and guest

- In virtual box, Devices>Insert Guest Additions CD Image. This installs guest additions for expanded functionality.
- Under virtual box, Settings>General>Advanced, enable Shared Clipboard.
- If you run into issues with permissions, go to /etc/fstab and add exec permission. To do this, change following in fstab file `/dev/sr0 /media/cdrom0 udf,iso9660 user,noauto 0 0` to `/dev/sr0 /media/cdrom0 udf,iso9660 user,noauto,exec 0 0`. You may need sudo to do this.


## Shared folder b/w host and guest

- In virtual box, Devices>Insert Guest Additions CD Image. This installs guest additions for expanded functionality.
- In virtual box, Settings>Shared Folders, add the folder you would like to share between host and guest.
- From a terminal in guest, run `sudo adduser <username> vboxsf`.
- Restart virtual box.
