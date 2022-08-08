# MIT6.S081-xv64-lab

This repository contains my solution to the labs for MIT's 6.S081 operating system and related resource I used in my learning.

## Resources

1. course home page：https://pdos.csail.mit.edu/6.828/2021/schedule.html
2. 课程视频中文文字版： https://mit-public-courses-cn-translatio.gitbook.io/mit6-s081
3. 课程视频中英字幕B站：https://www.bilibili.com/video/BV19k4y1C7kA?spm_id_from=333.1007.top_right_bar_window_custom_collection.content.click



## How to use official lab skeleton?

First, you need to clone this repository by

```c
git clone git://g.csail.mit.edu/xv6-labs-2021
```

Then cd into the file, you are now in the master branch of the projects, to see my answer to a specific lab, e.g. util, syscall ...... , you just checkout into that branch by for example 

```
git checkout util
```

and now you are in the utils branch which contains my solution to the specific lab. 

if you want to have a clean copy of the original lab handout, just go to the [course website](https://pdos.csail.mit.edu/6.828/2020/schedule.html) and follow the lab guidance. Also, you can watch the course videos on the course website. Hope you enjoy your OS journey.



## Lab env Set up
reference to https://pdos.csail.mit.edu/6.828/2021/tools.html

```shell
$ sudo apt-get update && sudo apt-get upgrade
$ sudo apt-get install git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu
```
**my problem**

GDB env

all done, but my problem is that I cannot get the right g env right
solutions are the follows：
* vim a new file .gdbinit in the ~ directory
  ```shell
  vim ~/.gdbinit
  ```
  paste the followings into it
  ```txt
  add-auto-load-safe-path yourpath/.gdbinit
  ```
* and run
  ```shell
  gdb-muiltharch
  ```

  

## refer to my implement for this lab

clone this rep

> git clone git@github.com:hxhcreate/MIT6.S081-xv64-lab.git

switch to specific branch eg:

> git checkout -b util
