ToyRobot_AceBelaro
========

Toy Robot Implementation in C++

## Getting Started

You'll need to do have the following:
* GNU Make (for windows tested with GNU make v4.3)
* g++ that supports C++14 (for windows tested with 8.1.0)
* git

## Building
You can build the console application via Visual Studio IDE (see ide_project/vs) or via makefile.
#### By Makefile
```
make
ToyRobot
```
## Running Tests
You can run the unit tests via Visual Studio IDE (see ide_project/vs) or via makefile.
```
git submodule update --init --recursive
make tests
test_ToyRobot
```

### Notes
* When using Visual Studio IDE, download package `Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn.1.8.1.5`
