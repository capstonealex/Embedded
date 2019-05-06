# Building kernel and replacing existing kernel

The instructions here detail cross compiling debian kernels maintained by Robert Nelson (Official BBB Kernel Maintenance). His [ti-linux-kernel-dev](https://github.com/RobertCNelson/ti-linux-kernel-dev) repo has branches with prepatched RT kernels that can be deployed on the BBB.

## Overview

1. Create a clone of Robert Nelson's ti-linux repos and checkout the appropriate kernel branch.
2. Compile kernel using either build_kernel (builds kernel files) or build_deb (builds kernel files as debian packages) scripts.
3. Live boot the BBB with a functioning debian image.
4. Copy the kernel files or debian packages (generated in step 2) on the live booted BBB.
5. Install the kernel files on to the SD card image (used for livebooting).
6. Flash the BBB with the modified image on the SD card.

## Building Kernel

These steps should be done on the host PC and not the BBB as there are large file downloads and resource intense compilations.

1. Git clone the Robert Nelson's ti-linux-kernel-dev repo: `git clone https://github.com/RobertCNelson/ti-linux-kernel-dev.git`
2. Git checkout the appropriate kernel branch. For these instructions, the 4.14 RT kernel will be used. `git checkout ti-linux-rt-4.14.y`
3. The working folder should contain a `build_kernel.sh` and `build_deb.sh` script file. Either can be used to build a kernel. The latter is recommended as it creates packages that are easier to deploy in a debian environment.
4. Run either of the scripts. It may throw an error stating that some dependencies need to be installed. Install them as prompted. Once you have the dependencies, run the build script again.
5. A kernel configuration prompt will pop up. It can be left as default. Or you can load the kernel configuration from a properly function BBB (found in the `/boot` folder of the BBB). _More research needs to be done into configuring the kernel_.
6. The compilation will resume. On a laptop (i5-8250U CPU, 8GB RAM) running a VM (2 cores, 2 GB RAM), it takes approximately an hour.
7. Once the compilation is complete, there will be sub folder called "deploy".
   - if you used the build_kernel.sh script, there will be a `4.14.108-ti-rt-r103.zimage`, `4.14.108-ti-rt-r103-dtbs.tar.gz` and `4.14.108-ti-rt-r103-module.tar.gz` files. The file names will depend on the kernel version you checked out earlier.
   - if you used the build_deb.sh script, there will be a `linux-headers-4.14.108-ti-rt-r103_1xross_armhf.deb` , `linux-image-4.14.108-ti-rt-r103_1xross_armhf.deb` and `linux-libc-dev_1xross_armhf.deb` files. The file names will depend on the kernel version you checked out earlier.

## Installing the kernel built with build_deb.sh method (recommended)

1. [Live boot](https://github.com/capstonealex/Embeded/wiki/Flashing-&-Livebooting-images-on-the-BBB) the BBB using a functioning image on SD card.
2. Copy the .deb files from the deploy folder on to the BBB.
3. Install the three packages: `sudo dpkg -i <package name>.deb`
4. The SD card now has an image with the new kernel. You can now live boot or flash this image.

## Installing the kernel built with build_kernel.sh method

1. [Live boot](https://github.com/capstonealex/Embeded/wiki/Flashing-&-Livebooting-images-on-the-BBB) the BBB using a functioning image on SD card.
2. Copy the zimage and 2 tar.gz files from the deploy folder on to the BBB.
   - The zimage should be placed in the `\boot\` folder and renamed to `vmlinuz-<kernel_version>`. Remove the `.zimage` extension from the file name. This can also be done via terminal: `sudo cp -v <kernel_version>.zImage /boot/vmlinuz-<kernel_version>`. Replace <kernel_version> with the compiled kernel version.
   - The device tree binaries files (dtbs) should be extracted and copied to `/boot/dtbs/` folder.
     `sudo mkdir -p /boot/dtbs/<kernel_version>/` followed by `sudo tar xfv <kernel_version>-dtbs.tar.gz -C /boot/dtbs/<kernel_version>/`
   - The kernel modules should be copied to `/` (i.e root) folder. `sudo tar xfv <kernel_version>-modules.tar.gz -C /`
3. Generate initrd by running `sudo update-initramfs -ck <kernel_version>`
4. Update `/boot/UEnv.txt` line `uname_r=<kernel_version>` with new kernel version.
5. The SD card now has an image with the new kernel. You can now live boot or flash this image.

## Additional Information

- If you want to go back to the old kernel. Simply edit the `/boot/uEnv.txt` file and change the line `uname_r=<kernel>` to the appropriate kernel version. Make sure you only use kernels that are installed on the system. You can check installed kernels by running `dpkg --list | grep linux-image`

## Sources

- Manual installation of kernel files (build_kernel.sh method) https://www.digikey.com/eewiki/display/linuxonarm/BeagleBone+Black#BeagleBoneBlack-InstallKernelandRootFileSystem
- BBB Github wiki about kernel cross compilation https://github.com/beagleboard/linux/wiki
