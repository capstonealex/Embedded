# Workbench
## Option A. Cross compile on a host machine.
### Using Docker to Cross-Compile
Docker is a light-weight virtual machine with excellent cross-platform support. This allows us to run something very close to the Target OS(Beagle bone black in this case) on any desktop or notebook computer. We get the same versions of all of the libraries running on the Target machine but compile with the power of a desktop processor.
1. Install Docker and Docker hub[Docker Desktop for Mac and Windows | Docker](https://www.docker.com/products/docker-desktop)
2. docker pull alejandro4siana/cross-bbb-debian
3. cd into the file you wish to cross compile in (e.g. CORC)
```
docker run siana/cross-bbb-debian > bbbxc
chmod +x bbbxc
```
4. run the command `./bbbxc make exe    ` which should create your executable ready to upload onto Target machine
5.(OPTIONAL) Install vscode and use docker container as compiling environment:[VS code](https://code.visualstudio.com/docs/remote/containers)

### Prebuilt GNU Toolchains for Windows
- Windows developers can use a pre-build GCC compiler for C and C++ languages locally on their host machine.
- The PreBuilt GNU Windows toolchain and accompanying plugin for Visual Studio can be found here: [Link](https://gnutoolchains.com/beaglebone/)
- Once installed, a call to cross-compile to an armhf target will use this compiler.

## Option B. Build a virtual machine and cross-compile

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

- In the virtual box, Devices>Insert Guest Additions CD Image. This installs guest additions for expanded functionality.
- Under virtual box, Settings>General>Advanced, enable Shared Clipboard.
- If you run into issues with permissions, go to /etc/fstab and add exec permission. To do this, change following in fstab file `/dev/sr0 /media/cdrom0 udf,iso9660 user,noauto 0 0` to `/dev/sr0 /media/cdrom0 udf,iso9660 user,noauto,exec 0 0`. You may need sudo to do this.


## Shared folder b/w host and guest

- In virtual box, Devices>Insert Guest Additions CD Image. This installs guest additions for expanded functionality.
- In virtual box, Settings>Shared Folders, add the folder you would like to share between host and guest.
- From a terminal in guest, run `sudo adduser <username> vboxsf`.
- Restart virtual box.
