## Setting up Virtual Machine

<!-- EXPLAIN HOW THE BELLOW WAS BUILT -->

For development we suggest using a virtual machine (VM) running debian (stretch) linux.
Follow these steps to start running a pre-configured VM .ova file on your own machine.
The pre-configured VM has been configured as outlined in the [workbench setup](https://embeded.readthedocs.io/en/latest/workbench/) section.
Upon installation the user should have an environment capable of developing software, testing and cross-compiling to a real time linux OS on a Beagle Bone Black.

1. Install [virtual box version 6.0.4](<https://www.virtualbox.org/wiki/Download_Old_Builds_6_0>).
2. Download and install the VirtualBox Oracle VM VirtualBox [Extension Pack](https://www.virtualbox.org/wiki/Downloads).
2. Download workbench.ova: Currently hosted at the capstone google drive: [workbench.ova](https://drive.google.com/drive/folders/1lCGyRpQLjKOnCXbs27e6w6VfofizSCC8)

    * Google Drive Location: `Capstone Project - LOWER LIMB EXOSKELETON FOR GAIT ASSISTANCE\Embedded Team\Virtual Machines`
   Note: You may need a University of Melbourne email to access this link.

3. In Virtual box `file -> import appliance` and enter the path to the .ova file

4. Configure the environment .

    * Select 70mb or more of video ram.

5. Make sure to select the `reinitialize the MAC address of all the network cards option`.

6. Start your system and install virtual box Guest additions.

    * Login password is `password`

## Guest additions for VM

On the Virtual box menu Choose “Devices”->”Insert Guest Additions CD image…”

If this does not automatically run then follow the below code on a terminal.

```
user@debian:~$ su -
root@debian:~# apt-get update
root@debian:~# apt-get install build-essential module-assistant
root@debian:~# m-a prepare
root@debian:~# cd /media/cdrom
root@debian:~# sh ./VBoxLinuxAdditions.run
root@debian:~# reboot
```

## Testing the VM
* Follow the tests run in [cross compilation test](https://embeded.readthedocs.io/en/latest/crosscomp/#test-installation) section.
* Follow the instructions in [eclipse cross compilation](https://embeded.readthedocs.io/en/latest/eclipse/) section.
    
You should now have a cloned VM with working Debian and cross compilation to BBB or any other armhf devices.