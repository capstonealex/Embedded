# Building kernel and replacing existing kernel

The instructions here detail cross compiling debian kernels maintained by Robert Nelson (Official BBB Kernel Maintenance). His [ti-linux-kernel-dev](https://github.com/RobertCNelson/ti-linux-kernel-dev) repo has branches with prepatched RT kernels that can be deployed on the BBB.

## Overview

1. Create a clone of Robert Nelson's ti-linux repos and checkout the appropriate kernel branch.
2. Compile kernel using build_deb (builds kernel files as debian packages) scripts.
3. Live boot the BBB with a functioning debian image.
4. Copy the debian packages (generated in step 2) on the live booted BBB.
5. Install the kernel files on to the SD card image (used for livebooting).
6. Flash the BBB with the modified image on the SD card.

## Building Kernel

These steps should be done on the host PC and not the BBB as there are large file downloads and resource intense compilations.

1. Git clone the Robert Nelson's ti-linux-kernel-dev repo: `git clone https://github.com/RobertCNelson/ti-linux-kernel-dev.git`
2. Git checkout the appropriate kernel branch. For these instructions, the 4.14 RT kernel will be used. `git checkout ti-linux-rt-4.14.y`
3. Navigate to the local folder with the repo:`cd ti-linux-kernel-dev`. This folder should contain a `build_deb.sh` script file. This creates packages that are easy to deploy in a debian environment.
4. Run this script. It may throw an error stating that some dependencies need to be installed. Install them as prompted. Once you have the dependencies, run the build script again.
5. A kernel configuration prompt will pop up. It can be left as default. Or you can load the kernel configuration from a properly function BBB (found in the `/boot` folder of the BBB). _More research needs to be done into configuring the kernel_.
6. The compilation will resume. On a laptop (i5-8250U CPU, 8GB RAM) running a VM (2 cores, 2 GB RAM), it takes approximately an hour. Outside the VM is takes roughly 20mins.
7. Once the compilation is complete, there will be sub folder called "deploy".
   - This folder has `linux-headers-4.14.108-ti-rt-r103_1xross_armhf.deb` , `linux-image-4.14.108-ti-rt-r103_1xross_armhf.deb` and `linux-libc-dev_1xross_armhf.deb` files. The file names will depend on the kernel version you checked out earlier.
   
The debian packages compiled in this section can be found [here](https://drive.google.com/drive/folders/1QxixLCkjTl1fydw8D9Qf-CXiwcgkRjLf?usp=sharing). Note: You may need a University of Melbourne email to access this.

## Installing the kernel built with build_deb.sh method

1. [Live boot](https://exoembedded.readthedocs.io/en/latest/bbb/#getting-and-flashing-bbb-images) the BBB using a functioning image on SD card.
2. Copy the .deb files from the deploy folder on to the BBB.
3. From the terminal, navigate to the folder where you copied the .deb file. Install the three packages: `sudo dpkg -i <package name>.deb`
4. The SD card now has an image with the new kernel. You can now live boot or flash this image.

## Additional Information

- If you want to go back to the old kernel, edit the `/boot/uEnv.txt` file in the SD card debian image. Change the line `uname_r=<kernel>` to the appropriate kernel version. Then [flash](https://exoembedded.readthedocs.io/en/latest/bbb/#getting-and-flashing-bbb-images) the BBB with this image. Make sure you only use kernels that are installed on the system. You can check installed kernels by running `dpkg --list | grep linux-image`

## Real-time Tests
### Cyclic Test
1. Download the rt-test files from [https://mirrors.edge.kernel.org/pub/linux/utils/rt-tests/](https://mirrors.edge.kernel.org/pub/linux/utils/rt-tests/)
2. Extract them into a folder on the BBB. 
3. Run `make all`. Run 'make NUMA=0' if you encounter errors with the former. 
4. `sudo ./cyclictest -p 80` while in the working folder will start the cyclic test. `-p 80` is for priority.
5. Run a cpu stress test at same time while benchmarking. Get debian package for stress from here [https://packages.debian.org/stretch/armhf/stress/download](https://packages.debian.org/stretch/armhf/stress/download). Copy to BBB and install using dpkg.
6. Follow instructions here [http://zeuzoix.github.io/techeuphoria/posts/2015/04/21/benchmarking-rt-preempt-kernel-on-beaglebone-black/](http://zeuzoix.github.io/techeuphoria/posts/2015/04/21/benchmarking-rt-preempt-kernel-on-beaglebone-black/)
7. More instructions here: [https://wiki.linuxfoundation.org/realtime/documentation/howto/tools/rt-tests](https://wiki.linuxfoundation.org/realtime/documentation/howto/tools/rt-tests) and [https://web.archive.org/web/20160716124520/https://rt.wiki.kernel.org/index.php/Cyclictest](https://web.archive.org/web/20160716124520/https://rt.wiki.kernel.org/index.php/Cyclictest) (accessed via wayback machine)

## Sources

- Manual installation of kernel files (build_kernel.sh method) [https://www.digikey.com/eewiki/display/linuxonarm/BeagleBone](https://www.digikey.com/eewiki/display/linuxonarm/BeagleBone)+Black#BeagleBoneBlack-InstallKernelandRootFileSystem
- BBB Github wiki about kernel cross compilation [https://github.com/beagleboard/linux/wiki](https://github.com/beagleboard/linux/wiki)
- [Robert Nelson's Repo](https://github.com/RobertCNelson/ti-linux-kernel-dev)

# Alternate Methods

There is an alternate script `build_kernel.sh` that can be used to make non-debian specific kernel files. In step 4 of the "Building Kernel" section, run this script instead to generate kernel files. In step 7, the deploy folder will contain `4.14.108-ti-rt-r103.zimage`, `4.14.108-ti-rt-r103-dtbs.tar.gz` and `4.14.108-ti-rt-r103-module.tar.gz` files. The file names will depend on the kernel version you checked out earlier. Now, follow the instructions below to install these kernel files.

### Installing the kernel built with build_kernel.sh method

1. [Live boot](https://exoembedded.readthedocs.io/en/latest/bbb/#getting-and-flashing-bbb-images) the BBB using a functioning image on SD card.
2. Copy the zimage and 2 tar.gz files from the deploy folder on to the BBB.
   - The zimage should be placed in the `\boot\` folder and renamed to `vmlinuz-<kernel_version>`. Remove the `.zimage` extension from the file name. This can also be done via terminal: `sudo cp -v <kernel_version>.zImage /boot/vmlinuz-<kernel_version>`. Replace `<kernel_version>` with the compiled kernel version.
   - The device tree binaries files (dtbs) should be extracted and copied to `/boot/dtbs/` folder.
     `sudo mkdir -p /boot/dtbs/<kernel_version>/` followed by `sudo tar xfv <kernel_version>-dtbs.tar.gz -C /boot/dtbs/<kernel_version>/`
   - The kernel modules should be copied to `/` (i.e root) folder. `sudo tar xfv <kernel_version>-modules.tar.gz -C /`
3. Generate initrd by running `sudo update-initramfs -ck <kernel_version>`
4. Update `/boot/UEnv.txt` line `uname_r=<kernel_version>` with new kernel version.
5. The SD card now has an image with the new kernel. You can now live boot or flash this image.
