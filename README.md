# Revision History
|  Date  | Log  | Written by   | Confirmed By  | 
|---|---|---|---|
|  6 Oct 2018 | First draft  | Seokhwan Kim |  User  |
|  8 Oct 2018 | scripts directory added, sn_exception class added  | Seokhwan Kim |  User  |
|  11 Oct 2018 | CMake support is added  | Seokhwan Kim |  User  |
|  14 Oct 2018 | deque based map added  | Seokhwan Kim |  User  |
|  16 Oct 2018 | vector based map added  | Seokhwan Kim |  User  |
|  17 Oct 2018 | performance test result added   | Seokhwan Kim |  User  |
|  3 Nov 2018 | performance test without exception check | Seokhwan Kim |  User  |

# SN_STL 
sn_stl is a small implementation of stl (c++ standard template library) for <strong>complex realtime software</strong>.

You can find the full documentation of the SN_STL at https://seokhwan.github.io/

## What is the complex realtime software ? 
The complex realtime software generally runs on the following environment : <br>
1. There is a handy RTOS: Xenomai / RT preempt patched Linux, VxWorks, or INtime on Windows
2. It runs on relatively high performance embedded chipsets: <br>
666Mhz ARM Cortex-A9 chip with 512 MB RAM is an example 

The examples of such complex realtime software are : <br>
* Robot / Motion control software
* Any control software that requires lots of math

The characteristics of those complex realtime software are : 
* <strong>The OS, HW resource is solely for me : </strong>the desktop / mobile software should consider the other software. For example, if your loop consumes all CPU, then the other software are stuck. No user and developer do want this. So you should be very carefult that your software doesn't consume too much CPU and memory. Many people think the embedded software should be more optimized and suffer the lack of resource. That is generally true but also it is not true for some aspects. In this environment, even though your application runs on an operating system, you do not need to consider the other processes. You can (also must) use all resource as much as possible.
* <strong>Still RT software techniques necessary : </strong> Even though you have lots of memory and whole CPU available, still it is RT software. Therefore, you need to avoid unencouraged habits such as runtime memory allocation / deallocation or the complex multi-threaded routines with lots of lock() / unlock() statements.

## So why SN_STL? 
### You need to know it eactly
<strong>The second characteristics (RT techniques necessary) </strong> requires you to use an algorithm or data structure that <strong>you fully understand</strong>.

I know STL implementations in g++ or Microsoft CL compilers are superior. The code of STL in those popular compilers are written by super developers and intensively tested for numerous exceptional cases. Generally, there is very little possibility that we can write such high quality code before the end of our life. I do know. But, the code is highly complex so that generally we do "not know it exactly".

If resize() happens in std::vector, how much time and memory is really required in terms of O() notation? In your code how many times the resize() happens? As a developer who deals with reliable software we must be able to answer it. Otherwise, it is better to have some clumsy and bit slow but highly understandable implementations.

The worse is if your software runs on different OS (it generally happens when you develop the complex realtime software), each implementation of STL is also little bit different. Can you really exactly know the difference? How about if the compiler's version is updated? Do you really know that how much the std::vector is different from the previous version?

<strong>If you don't know it exactly, something undebuggable happens</strong>. That's what I have learned through more than 15 years of development exoerience. I don't want to face such situation again. I do want to know it more exactly.

### You can know it eactly
Most of codes are under few hundreds lines, and no function is more than 100 lines. I know lines of code is not matter. However, the less line the less you need to read and understand. And more possibility of knowing it exactly.

### Design
The key designs that are different from standard STL are : <br>
* <strong>No automatic allocation</strong><br>
It does not call resize() automatically. If overflow happens, it generates exception (not general exception). Even the complex realtime system, it is generally much more static than desktop software. The "static" in here means that you can know how much memory slots are required at maximum at compile time. So, generally it is better to make an exception to make you know you need more memory than to smoothly call resize() in the inside (then you will never recognize it).

* <strong>No undefined behavior</strong><br>
If you access a location of out of bound in std::vector, it just accesses it and segmentation fault occurs. This is a undefined behavior. See [vector's operator[] page](http://www.cplusplus.com/reference/vector/vector/operator[]/)). Generally this approach is not welcomed in the embedded software. If an exception occurs, sometimes the RT environment itself is crashed so that the system shows a undefined behavior (It happens in Xenomai env.). Rather than, calling a callback function (pre-defined) or gently reporting it is more welcomed way. Indeeed this is the critical requirement for the safety-critical software.

* <strong>Run as STL does</strong><br>
The SN_STL is a small set of STL and designed for different purpose. However, it is also designed to run in the same way of the STL. The same results for the same interfaces are greatly help to users. It must be.

# How to run
## Running Script
All process of building, execution, and generating coverage is wholly automated. You can run all them by script files. 

First, go to ./scripts directory first.

## Windows Environment
### Prerequisite
- Visual Studio 2017 Build Tool <br>
  You can download the build tool from [here](https://visualstudio.microsoft.com/en/downloads/)
  
- Windows Dependency <br>
  If you have cmake and opencppcoverage tools on your local machine and they are under the path, then it is not necessary. Otherwise, you can downlaod windows dependencies from the [link](https://github.com/seokhwan/deps/blob/master/sn_stl/deps_win.7z). The location of the deps_win directory should be as follows.
  ~~~
    C:\SN_STL
    ├─codes
    ├─deps_win
    ├─cripts
    ├─.gitignore
    ├─LICENSE
    └─README.md
  ~~~
  
### Build & Run
Please go to ./script/win, then you can see 
- 100_cmake.bat <br>
  it generates visual stuio solution using cmake.
- 200_build.bat <br>
  it builds the generated solution.
- 300_run.bat
  it actually executes the built files
- 400_coverage.bat
  optionally you can generate coverage data. The report is generated at ./doc/opencpp
- 900_clean.bat <br>
  it just cleans up build and doc directories

As the file names designate, it is straightforward. You can run the scripts in order.

## Ubuntu Environment
### Prerequisite
- cmake <br>
  you can install the cmake by the following command
  ~~~ bash
  sudo apt-get install cmake
  ~~~
- g++ compiler <br>
  also you can install it by the following command
  ~~~ bash
  sudo apt-get install g++
  ~~~

Then, go to ./script/ubuntu
- 000_prep.sh <br>
  it converts windows formatted files to unix format (i.e., dos2unix). If you have trouble to build the code, you need to run it first. Otherwise, it is not necessary.
- 100_cmake.sh <br>
  it generates Makefile using cmake.
- 200_build.sh <br>
  it builds the Makefile.
- 300_run.sh <br>
  it runs the built file.
- 900_clean.sh <br>
  it cleans up build and doc directories

# Performance Test

## TEST #001 std::map, sn_bbst, sn_map_deq, sn_map_vec  (17 Oct 2018)
I use std::map for following scenarios
* An efficient way to search() is necessary
* The key values are not consecutive

The general methods I use is emplace() and find() I compare the performance of two functions with respect to given item size. Please see the test code [TF0001_STDMAP_PERF](https://github.com/seokhwan/sn_stl/blob/master/codes/src/test/03_perf/TF0001_STDMAP_PERF.cpp)

## @Windows 10
Test Environment : 
* Microsoft (R) C/C++ Optimizing Compiler Version 19.15.26730 for x86
* Microsoft Windows [Version 10.0.17134.345]
* Intel(R) Core(TM) i7-7820 HQ
* 32GB RAM
  
### emplace (time unit : ms)
|ITEM SIZE  | std::map  | sn_map_vec   | sn_bbst  |  sn_map_deq | 
|---|---|---|---|---|
|  100 | 0.0112  | 0.0069 | 0.0139 | 0.0128 |
|  1000 | 0.1167  | 0.1155 | 0.1806  | 0.7500 |
|  10000 | 1.4055  |  3.8970 |  2.6033 |  67.8041 |
|  100000 | 20.9784 | 58.0564 | 26.0035  | 4377.99 |



### find (time unit : ms)
|ITEM SIZE  | std::map  | sn_map_vec   | sn_bbst  |  sn_map_deq | 
|---|---|---|---|---|
|  100 |  0.0042  | 0.0049 |  0.0039 | 0.0041 |
|  1000 | 0.0539  | 0.0668 |   0.0568 | 0.0451 |
|  10000 | 1.0730  |   0.9339 |  1.09675 |  0.70040  |
|  100000 | 13.7743  |  9.3541  | 17.3691 | 9.3837 |


## @Ubuntu 18.04 (GCC)
* g++ Ubuntu 7.3.0-27ubuntu1~18.04
* Linux 4.15.0-36-generic #39-Ubuntu
* Intel(R) Core(TM) i7-7820 HQ
* 32GB RAM
  
### emplace (time unit : ms)
|ITEM SIZE  | std::map  | sn_map_vec   | sn_bbst  |  sn_map_deq | 
|---|---|---|---|---|
|100 | 0.00539 |   0.0043 |  0.0117 | 0.0066 |
|1000 | 0.0730 |   0.0730 |  0.1569 |  0.3678 |
| 10000 |  1.2360 | 2.8669 | 2.8016 | 33.4804 |
| 100000 | 20.2375 | 361.7400 | 44.3311 | 4401.5100 |


### find (time unit : ms)
|ITEM SIZE  | std::map  | sn_map_vec   | sn_bbst  |  sn_map_deq | 
|---|---|---|---|---|
| 100 |  0.0024 | 0.0036 |  0.0034 |  0.0024 |
| 1000 | 0.0429 |  0.0528 | 0.0617 | 0.0445 |
| 10000 | 0.9791 |  0.7636 |  1.2157 |  0.34650 |
| 100000 | 17.9325 | 10.3999 | 20.3142 | 6.8370 |

## @Ubuntu 18.04 (Clang)
* clang version 6.0.0-1ubuntu2 
### emplace (time unit : ms)
|ITEM SIZE  | std::map  | sn_map_vec   | sn_bbst  |  sn_map_deq | 
|---|---|---|---|---|
| 100 |  0.0051 |  0.0050 |  0.0119 |  0.0083 |
| 1000 | 0.0650 | 0.0853 |  0.1813 | 0.4791 |
| 10000 | 1.0827 | 3.09479 | 2.9315 | 56.9163 |
| 100000 | 18.1623 | 365.9190 | 47.7129 | 5588.2200 |


### find (time unit : ms)
|ITEM SIZE  | std::map  | sn_map_vec   | sn_bbst  |  sn_map_deq | 
|---|---|---|---|---|
| 100 | 0.0013 | 0.0038 | 0.0034 |  0.0035 | 
| 1000 | 0.0249  | 0.0584 | 0.0618 | 0.0560 | 
| 10000 | 0.51865 | 0.8246 | 1.1468 | 0.6326 | 
| 100000 | 10.4149 | 11.6132 | 19.7357 | 8.98817 |

## TEST #002 Without Exception Check
Throughout  [the first performance test](#test-001-stdmap-sn_bbst-sn_map_deq-sn_map_vec--17-oct-2018) I could find the good performance balance of std::map. It showed the best performance for emplace() with still relatively reasonable performance for find(). 

Actually my implementaion with vector and deque is based on simple sorted array. Because it uses insertion sort, the poor performance for emplace with relatively large data is obvious. However, why the performance of the find() not much better than the std::map ? 

The answer was because of exception check (i.e., checking memory boundary). The implementation of operator[] contained the following code. 
~~~
if (idx >= m_size)
{
  exception_handle();
}
~~~

The effect of the boundary check was huge more than I expect. The following result is without such boundary check.


## @Windows 10
Test Environment : 
* Microsoft (R) C/C++ Optimizing Compiler Version 19.15.26732.1 for x86
* Microsoft Windows [Version 10.0.17134.376]
* Intel(R) Core(TM) i7-7820 HQ
* 32GB RAM
  
### emplace (time unit : ms)
|ITEM SIZE  | std::map  | sn_map_vec   | sn_bbst  |  sn_map_deq | 
|---|---|---|---|---|
| 100    | 0.0129        | 0.0059        | 0.0150        | 0.0081        |
| 1000   | 0.1320        | 0.0992        | 0.2123        | 0.3547        |
| 10000  | 1.8617        | 3.7310        | 3.0529        | 22.7365       |
| 100000 | 22.7014       | 53.3589       | 26.5422       | 292.9138      |

### find (time unit : ms)
|ITEM SIZE  | std::map  | sn_map_vec   | sn_bbst  |  sn_map_deq | 
|---|---|---|---|---|
| 100    | 0.0058        | 0.0041        | 0.0054        | 0.0048        |
| 1000   | 0.0761        | 0.0504        | 0.0724        | 0.0548        |
| 10000  | 1.1287        | 0.6339        | 1.2024        | 0.6825        |
| 100000 | 16.1198       | 7.4553        | 16.6245       | 8.0339        |

## @Ubuntu 18.04 (GCC)
* g++ Ubuntu 7.3.0-27ubuntu1~18.04
* Linux 4.15.0-38-generic #41-Ubuntu 
* Intel(R) Core(TM) i7-7820 HQ
* 32GB RAM
  
### emplace (time unit : ms)
|ITEM SIZE  | std::map  | sn_map_vec   | sn_bbst  |  sn_map_deq | 
|---|---|---|---|---|
| 100    | 0.0069        | 0.0045        | 0.0125        | 0.0070        |
| 1000   | 0.0951        | 0.0704        | 0.1831        | 0.2387        |
| 10000  | 1.3831        | 2.7005        | 2.9260        | 16.8448       |
| 100000 | 21.4425       | 359.7794      | 47.3907       | 1458.1417     |

### find (time unit : ms)
|ITEM SIZE  | std::map  | sn_map_vec   | sn_bbst  |  sn_map_deq | 
|---|---|---|---|---|
| 100    | 0.0050        | 0.0038        | 0.0050        | 0.0052        |
| 1000   | 0.0757        | 0.0484        | 0.0720        | 0.0699        |
| 10000  | 1.2226        | 0.5866        | 1.2422        | 0.9015        |
| 100000 | 20.3735       | 9.8720        | 20.5865       | 12.2228       |

## @Ubuntu 18.04 (Clang)
* clang version 6.0.0-1ubuntu2 
### emplace (time unit : ms)
|ITEM SIZE  | std::map  | sn_map_vec   | sn_bbst  |  sn_map_deq | 
|---|---|---|---|---|
| 100    | 0.0068        | 0.0051        | 0.0135        | 0.0087        |
| 1000   | 0.0806        | 0.0807        | 0.1923        | 0.3966        |
| 10000  | 1.3265        | 3.0671        | 3.2035        | 32.4414       |
| 100000 | 21.2073       | 363.8008      | 47.6511       | 2905.6070     |

### find (time unit : ms)
|ITEM SIZE  | std::map  | sn_map_vec   | sn_bbst  |  sn_map_deq | 
|---|---|---|---|---|
| 100    | 0.0041        | 0.0045        | 0.0053        | 0.0057        |
| 1000   | 0.0548        | 0.0606        | 0.0757        | 0.0760        |
| 10000  | 1.0669        | 0.7623        | 1.2585        | 0.8959        |
| 100000 | 21.2329       | 12.6067       | 20.4856       | 12.6275       |

# Acknowledge
As stated in sn_stl/sn_stl.h file, many of the source code is from the book [Data Structures & Algorithm Analysis in C++](https://www.amazon.com/Data-Structures-Algorithm-Analysis-C/dp/013284737X) by Prof. Mark Allen Weiss (Florida International University)

I really appreciate the effort and the great insight by the author.

# License
sn_stl is [New BSD License (or Modified BSD Licnese)](https://github.com/seokhwan/sn_stl/blob/master/LICENSE)