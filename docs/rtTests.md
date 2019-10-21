Newer instructions are being added here 


Quick Overview
Download the rt-test files from https://mirrors.edge.kernel.org/pub/linux/utils/rt-tests/
Extract them into a folder.
Run make all. Run 'make NUMA=0' if you encounter errors with the former.
sudo ./cyclictest -p 80 while in the working folder will start the cyclic test. -p 80 is for priority.
Run a cpu stress test at same time while benchmarking. Get debian package for stress from here https://packages.debian.org/stretch/armhf/stress/download. Copy to BBB and install using dpkg.
stress --cpu 64 --io 64 --vm 2  --timeout 120 --vm-bytes 128M &
Follow instructions here 


g++ GPIO/GPIOConst.cpp GPIO/GPIOManager.cpp -o swave square.cpp -lrt -Wall

## Additional Reading

* [https://wiki.linuxfoundation.org/realtime/documentation/howto/tools/rt-tests](https://wiki.linuxfoundation.org/realtime/documentation/howto/tools/rt-tests)

* [http://zeuzoix.github.io/techeuphoria/posts/2015/04/21/benchmarking-rt-preempt-kernel-on-beaglebone-black/](http://zeuzoix.github.io/techeuphoria/posts/2015/04/21/benchmarking-rt-preempt-kernel-on-beaglebone-black/)