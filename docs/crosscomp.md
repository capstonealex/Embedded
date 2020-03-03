# Cross-compilation tool chain on LINUX

## Install

The cross-toolchain repository on linux can be used for crosscompilation. Specifically, the ARM hard float (armhf) package can be used for building programs for the BBB.

- On the guest OS (Debian on VM), run the following command:
  ```apt-cache search cross-build-essential
     sudo apt install crossbuild-essential-armhf
  ```

## Test Installation

- Test installation by calling it directly: `arm-linux-gnueabihf-g++ -v`
- You should see the following output: `“COLLECT_GCC=arm-linux-gnueabihf-g++ … Thread model: posix gcc version 6.3.0 20170516 (Debian 6.3.0-18) ”`

## Test toolchain Compiler.

To test the tool chain, create a simple hello world program and cross-compile for ARM.

- `nano testcross.cpp`

```cpp
#include <iostream>
using namespace std;

int main()
{
    cout << "Hello, From amrhf architecture!";
    return 0;
}
```

- Compile with -static to statically build the executable.

```linux
user@desktop:~$ arm-linux-gnueabihf-g++ -static testcross.cpp -o testcross
```

- The above code will produce an executable file called `testcross`. This will not directly run on your computer since it has ARM machine code. You should see the following error if you try: `cannot execute binary file: Exec format error`
- Copy the testcross file on to the BBB.
- Run the program in BBB using:

```linux
./testcross
```

- It should print:`Hello, From amrhf architecture!`

## Emulate armhf architecture with QEMU

The cross compiled programs cannot be run on your computer (or Guest OS) since it has machine code for the ARM architecture. However, QEMU package can be used to emulate the armhf on the guest OS in VM. To do this:

- `sudo apt install qemu-user-static`
- Notify dpkg (package management system) that multiple architecture packages will be on the machine.

```linux
user@desktop:~$ sudo dpkg --add-architecture armhf
user@desktop:~$ dpkg --print-foreign-architectures
armhf ”
```

- Check for success with: `user@desktop:~$ sudo apt update`
- Return should have several packages ending in `armhf Packages` if not try again.
- You can also try running the `testcross` executable created in the prev section to verify that QEMU is installed correctly.
