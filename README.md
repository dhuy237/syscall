# System Call

This is a assignment of Operating Systems course (CO2018). \
The goal of this assignment is to understand steps of modifying, compiling and installing Linux kernel. In details, the task is add a new system call which helps applications to know the parent and the oldest child of a given process.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine.

### Prerequisites

Download and unpack the kernel source (kernel version 5.0.5):

```
$ wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux -5.0.5.tar.xz
$ tar -xvJf linux-5.0.5.tar.xz
```
### Configuration

```
$ cp /boot/config-$(uname -r) ˜/kernelbuild/.config
$ sudo apt-get install fakeroot ncurses-dev xz-utils bc flex libelf-dev bison
$ make nconfig
```
To change kernel version, go to "General setup" option, access the line "Local version - append to kernel release". Then enter a dot "." followed by the number of version. 

### Installing

Install the modules, we can run this stage in parallel by using tag "-j np", where np is the number of processes you run this command:

```
$ make -j 4 modules
$ sudo make -j 4 install
$ sudo make -j 4 modules_install
$sudo make -j 4 install
$ sudo reboot
```

Run the following command to check the result, it should print your kernel version:

```
uname -r
```
