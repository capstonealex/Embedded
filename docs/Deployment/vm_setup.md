## Setting up Virtual Machine

<!-- EXPLAIN HOW THE BELLOW WAS BUILT -->

For development we suggest using a virtual machine (VM) running debian (stretch) linux.
Follow these steps to start running a pre-configured VM .ova file on your own machine.
The pre-configured VM has been configured as outlined in the [workbench setup](https://exoembedded.readthedocs.io/en/latest/workbench/) section.
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
* Follow the tests run in [cross compilation test](https://exoembedded.readthedocs.io/en/latest/crosscomp/#test-installation) section.
* Follow the instructions in [eclipse cross compilation](https://exoembedded.readthedocs.io/en/latest/eclipse/) section.
    
You should now have a cloned VM with working Debian and cross compilation to BBB or any other armhf devices.

## Alternative Setup with Docker

Rather than setting up a Virtual Machine, an alternative is to use a Docker container to simulate the BBB on the user's host OS in a terminal. This method utilises cross compilation for the BBB, then copying the compiled exo app or tests to the Docker container to be run. A recommended method for setting up the Docker workflow on a fresh computer is described below.

1. Install [VSCode](https://code.visualstudio.com/)

2. Install [Git](https://git-scm.com/download)

3. Download the [GNU Toolchain](https://gnutoolchains.com/download/), selecting beaglebone-gcc6.3.0-r2.exe (361 MB) and install

4. Install [Docker](https://docs.docker.com/docker-for-windows/install)

   * Windows 10 Pro, Enterprise or Education are required for use. For University of Melbourne staff and students, a free upgrade to Windows 10 Education from Windows 10 Home can be accessed at [this link](https://unimelb.onthehub.com/WebStore/OfferingDetails.aspx?o=40f9cc62-6445-e511-940f-b8ca3a5db7a1)

   * To learn some of the basics on getting started with Docker, [this Youtube video](https://www.youtube.com/watch?v=t5yqLJfbnqM) may be useful.
   
5. Checkout the [code repository](https://github.com/capstonalex/exo)

6. Pull the armhf/Debian Docker image
   * Recommend using the VSCode terminals for simplicity, as multiple terminals will be required when the container is created. The following example was from a Powershell terminal within VSCode.
   
   ```
   PS C:\Users\pc-user> docker pull armhf/debian
   ```
   
7. Create a container based on the image

   * A container ID will be produced in the form of a long hexidecimal string.
   
   * This will not start the container yet.
   
   ```
   PS C:\Users\pc-user> docker create -it armhf/debian
   ```

8. Build the desired app or test using the relevant Makefile and the "make" command

   ```
   PS C:\Users\pc-user\Documents\Github\exo\> make testJoints
   ```

9. Copy the generated application on the local filesystem to the Docker container

   * Only enough characters of the container ID are needed to make it unique amoung created containers, so if only one container has been created, only one character of the container ID is needed.
   
   ```
   PS C:\Users\pc-user\Documents\Github\exo\> docker cp <APPNAME> <CONTAINERID>:/<LOCATION>
   ```
   
   * For example:
   
   ```
   PS C:\Users\pc-user\Documents\Github\exo\> docker cp testJoints 93d5d:/testJoints
   ````
   
10. Start the Docker container in interactive mode, using the flag '-i'

   ```
   PS C:\Users\pc-user\Documents\Github\exo\> docker start -i <CONTAINERID>
   ```

11. Confirm that the application copied from the local filesystem is present in the container and can be run

   * For example, listing the present files, running testJoints and exiting the container:
   
   ```
   root@93d5d77076e1:/exo# ls
   bin  boot  dev  etc  home  lib  media  mnt  opt  proc  root  run  sbin  srv  sys  testJoints  tmp  usr  var
   root@93d5d77076e1:/exo# ./testJoints
   This is a script to test the implementation of the Joints, ActuatedJoints and Drive Classes! 
   1. Construct a CopleyDrive Object (which implements Drive Class)
   2. Construct a TestActJoint Object (Cast as a ActuatedJoint), using the testDrive Object 
   MY JOINT ID: 1
   Read the ID of the Joint (Expected Value 1): 1
   Read Node ID of the Drive (Expected Value 100): 100
   Read Value of the Joint (Expected Value 0): 0
   Set the Joint into Position Control Mode: 1
   Set the position of the Joint to 1 (expected result: true): Drive 100 Writing 1 to 0x607A
   1
   Read Value of the Joint (Expected Value 0): 0
   Call a updateValue() defined in Joint: 1
   Read Value of the Joint (Expected Value 1): 1
   root@93d5d77076e1:/exo# exit
   ```
