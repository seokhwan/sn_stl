# Revision History
|  Date  | Log  | Written by   | Confirmed By  | 
|---|---|---|---|
|  6 Oct 2018 | First draft  | Seokhwan Kim |  User  |
|  8 Oct 2018 | script directory added, sn_exception class added  | Seokhwan Kim |  User  |

# SN_STL 
sn_stl is a small implementation of stl (c++ standard template library) for <strong>complex realtime software</strong>.

## What is the complex realtime software ? 
The complex realtime software runs on generally following environment : <br>
1. There is a handy RTOS: Xenomai / RT preempt patched linux, VxWorks, or INtime on Windows
2. It runs on relatively high performance embedded board: <br>
666Mhz ARM Cortex-A9 chip with 512 MB RAM is an example 

The examples of such complex realtiem software are : <br>
* Robot / Motion control software
* Any control software that requires lots of math

The characteristics of such complex realtime software is : 
* <strong>The OS, HW resource is solely for me : </strong>the desktop / mobile software shall consider the other software. For example, if your loop consumes all CPU then the other software are stuck. But in this environment, all OS and hardware resource are for your software only. You can use it as much as.
* <strong>Still RT software techniques necessary : </strong> Even though you have lots of memory and whole CPU available, still it is RT software. Therefore, you need to avoid unencouraged habits such as runtime memory allocation / deallocation or the complex multi-threaded routines with lots of lock() / unlock() statements.

## So why SN_STL? 
### You need to know it eactly
<strong>The second characteristics (RT techniques requried) </strong> requires you to use an algorithm or data structure that <strong>you exactly understand</strong>.

I know STL in G++ or Microsoft CL compilers are superior. The code of STL in those popular compilers are written by super developers and intensively tested for numerous exceptional cases. I will not be able to write such high quality code in my life. I do know. But, so the code is highly complex. 

If you are really familiar with the code of STL, you may be able to say that <strong> you know it exactly</strong>. But generally it is not true for general developers like me.

If resize() happens in std::vector, how much time and memory is really required in terms of O() notation? 

The worse is if your software runs on different OS (it generally happens when you develop the complext realtime software), each implementation of STL is also different. Can you really exactly know the difference? How about if the compiler's version is updated? You really know the vector is how much different from the previous version?

<strong>If you don't know it exactly, something undebuggable happens</strong>. That's what I have learned through more than 15 years of development. I don't want to face such situation again. I do want to know more exactly.

### You can know it eactly
SN_STL is writeen simply. I referred the book [Data Structures & Algorithm Analysis in C++](https://www.amazon.com/Data-Structures-Algorithm-Analysis-C/dp/013284737X) by the Prof. Mark A. Weiss. 

Most of codes are under few hundreds lines, and no function is more than 100 lines. I know lines of code is not matter. However, the less line the less you need to read and understand.

### Design
The key designs that are different from standard STL is : <br>
* <strong>No automatic allocation</strong><br>
It does not call resize() automatically. If overflow happens, it generates exception (not general exception). This is because you need to know how much slots you are using. So, the constructors of all implementations require the size argument.

* <strong>No undefined behavior</strong><br>
If you access a location of out of bound in std::vector, it just accesses it and segmentation fault occurs generally. This is a undefined behavior. See [vector's operator[] page](http://www.cplusplus.com/reference/vector/vector/operator[]/)). Generally this approach is not welcomed in the embedded software. If exception occurs the RT environment is crashed so that system itself shows a undefined behavior (It happens in Xenomai env.). Rather than, calling a callback function (pre-defined) or gently reporting it is more welcomed way. Indeeed this is the critical requirement for the safety-critical software.

* <strong>Run as STL does</strong><br>
The SN_STL is a small set of STL and designed for different purpose. However, it is also designed to run in the same way of the STL. The same results for the same interfaces are greatly help to developers. It must be.


