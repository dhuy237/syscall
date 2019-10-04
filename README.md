# System Call

This is a assignment of Operating Systems course (CO2018). \
The goal of this assignment is to understand steps of modifying, compiling and installing Linux kernel. In details, the task is add a new system call which helps applications to know the parent and the oldest child of a given process.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine. You should try this on the virtual machine because it can break your system easily. \
I use VirtualBox 6.0 tool.

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

### Trim the kernel

When install the kernel, it will take a long time to compile because it will include support for nearly everything so it is a general use and huge. \
You can trim your kernel with the following code:

```
$ make nconfig
```

For use in this course, I config the kernel with this code and select "No" with all the config:

```
$ make localmodconfig
```
### Add system call to the kernel

Create a folder with *sys_get_proc_info.c* and *Makefile* in linux-5.0.5/get_proc_info/ 

Then add get_proc_info/ to kernel Makefile:

```
$ pwd
~/kernelbuild/linux-5.0.5 //the folder of your kernel source
$ vim Makefile
```
Find the following line:

```
core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/
```

And add get_proc_info/:

```
core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ get_proc_info/
```

Add the new system call to the system call table: 

```
$ cd arch/x86/entry/syscalls/
$ echo "548 64 get_proc_info __x64_sys_get_proc_info" >> syscall_64.tbl
```

## Add new system call to the system call header:

```
$ ~/kernelbuild/include/linux/
```
Open syscalls.h and add the following line before #endif statement:

```
struct proc_info;
struct procinfos;
asmlinkage long sys_get_proc_info(pid_t pid, struct procinfos * info);
```
Then reinstall the kernel.

## Running the test

Compile *main.c* to see the test, the result should be my student ID (1752242), if yes, you successfully added the new system call to the kernel:
```
$ gcc main.c -o main
$ ./main
```

## Implement a wrapper

We need to implement a C wrapper for it to make it easy to use. This can be done outside the kernel.
```
$ sudo cp <path to get_proc_info.h> /usr/include
```
For example:
``` 
$ sudo cp ~/kernelbuild/code/get_proc_info.h /usr/include
```
Then: 
```
$ gcc -shared -fpic get_proc_info.c -o libget_proc_info.so
$ sudo cp ~/kernelbuild/code/libget_proc_info.so /usr/lib
```

## Run the system call

Open *htop* in the terminal to get the pid:

```
$ htop
```
For example, I take pid = 6189.
Compile the *valid.c* in the folder code/validation:

```
$ gcc valid.c -o valid -lget_proc_info
$ ./valid 6189
```

The result should print out the pid of parent and the oldest child of the current process.
