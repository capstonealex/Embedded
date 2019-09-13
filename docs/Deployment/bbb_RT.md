# Real-Time Kernel for BBB
This section shows how to install a pre-compiled RT kernel to your BBB.

1. Get the Debian kernel packages from [Capstone Project - LOWER LIMB EXOSKELETON FOR GAIT ASSISTANCE\Embedded Team\BBB Kernels](https://drive.google.com/drive/folders/1QxixLCkjTl1fydw8D9Qf-CXiwcgkRjLf?usp=sharing) of the Capstone Google Drive. 

    Note: You may need a University of Melbourne email ID.

2. [Live boot](https://embeded.readthedocs.io/en/latest/bbb/#live-booting-from-sd-card) the BBB using a functioning BBB Debian [image](https://embeded.readthedocs.io/en/latest/bbb/#getting-and-flashing-bbb-images) on SD card. For this project, we used a Debian stretch image obtained from the official BBB website.
2. Copy the .deb files from the 1st step on to the BBB.
3. From terminal on BBB, navigate to the folder where you copied the .deb file. Install the three packages: `sudo dpkg -i <package name>.deb`
4. The SD card now has an image with the new kernel. You can now [flash](https://embeded.readthedocs.io/en/latest/bbb/#getting-and-flashing-bbb-images) this image.