# BBB Full Image

* A full image of the BBB with sit stand state machine running is available [here](https://drive.google.com/drive/folders/1nDu9t-3D6QWoS1LQ1YXEao6SJg_YpuZZ?usp=sharing).
* This image can be flashed to the BBB as per instructions [here](https://exoembedded.readthedocs.io/en/latest/bbb/). The image is by default set on the non-RT kernel and the instruction to flash on the uEnv.txt file is commented out.
* The behaviour of this image is as follows:
   * `/etc/rc.local` starts the `/usr/bin/X2_startCAN.sh` and `/home/debian/Sit_stand/canopend/./ALEX` programs.
   * This starts CAN interface and sets BBB GPIO pins 8.7, 8.8, 8.9, 8.11 to input for the handheld control buttons. Then it starts the sit stand program located at `/home/debian/Sit_stand/canopend/./ALEX`.
   * The sit stand programs starts PDOs, does home calibration and then waits in IDLE state for user input. Press yellow button on hand controller to enter sit stand mode. Then Hold green button to cycle through sit stand. 
  
# Creating Your Own Image
  
  * Live boot with a fresh image of the BBB OS.
  * Set it up with required programs and startup scripts. These can be executed during startup by adding them to `rc.local`. Refer to [this](https://github.com/capstonealex/Embedded/tree/master/BBB%20Scripts/Startup%20Script%20-%20Full%20Program) for currently used startup scripts. 
  * Now shutdown BBB, take the SD card with the liveboot image and insert into Linux PC. 
  * Use `df -h` to identify the sd card.
  * Use `sudo dd if=/dev/mmcblk0p1 of=/SDCardBackup.img` to make the image. Replace `mmcblk0p1` with the appropriate partition.
  
  
