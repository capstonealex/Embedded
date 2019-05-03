## Editing BBB default sudo and root passwords

Username: debian

Password (also for sudo): temppwd

Root password: root

---

# Connect to BBB through VM

## Basic description of this here

## Setting up BBB outside VM (To be done first)

1. Fully shutdown VirtualBox and plug the BBB in to the host computer's USB. It should show up as a USB drive.
2. Install the correct BBB drivers for your host OS. These can be obtained from the http://beagleboard.org/getting-started. Note: The drivers stored in the BBB that shows up as USB device (on your computer) maybe outdated.
   - If the drivers were installed correctly, you should be able to remote login to the BBB (root@192.168.7.2 or debian@192.168.7.2 with password: temppwd) using Putty (Win) or SSH (linux/mac).

---

## Setting up VirtualBox to enable USB ethernet connection to BBB.

1. Download and install the VirtualBox Oracle VM VirtualBox Extension Pack (https://www.virtualbox.org/wiki/Downloads)
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
