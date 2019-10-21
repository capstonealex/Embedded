# Real Time Tests
This section contains information on benchmarking the OS after it has been patched with a RT kernel.

## Option 1: Cyclic Test

1. Download the rt-test files from [https://mirrors.edge.kernel.org/pub/linux/utils/rt-tests/](https://mirrors.edge.kernel.org/pub/linux/utils/rt-tests/). Also available in the RT tests folder.
2. Extract them into a folder on the BBB. Run `make all` on a terminal. Run `make NUMA=0` if you encounter errors with the former.
3. You can now start a cyclic test by running `sudo ./cyclictest -p 80` in the same folder. If you run without `-p 80`, there is no RT priority.
4. Run a cpu stress test at same time while benchmarking. You can use [stress](https://packages.debian.org/stretch/armhf/stress/download). Also available in the RT tests folder.
5. Copy to the stress deb packages to BBB and install using `sudo dpkg -i <package name>.deb`.
6. Run stress test for 120s using: `stress --cpu 64 --io 64 --vm 2  --timeout 120 --vm-bytes 128M &`

## Square Wave


g++ GPIO/GPIOConst.cpp GPIO/GPIOManager.cpp -o swave square.cpp -lrt -Wall

## Additional Reading

* [https://wiki.linuxfoundation.org/realtime/documentation/howto/tools/rt-tests](https://wiki.linuxfoundation.org/realtime/documentation/howto/tools/rt-tests)

* [http://zeuzoix.github.io/techeuphoria/posts/2015/04/21/benchmarking-rt-preempt-kernel-on-beaglebone-black/](http://zeuzoix.github.io/techeuphoria/posts/2015/04/21/benchmarking-rt-preempt-kernel-on-beaglebone-black/)

* [https://rt.wiki.kernel.org/index.php/Squarewave-example](https://rt.wiki.kernel.org/index.php/Squarewave-example)