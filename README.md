ToyRobot_AceBelaro
========

Toy Robot Implementation in C++

## Getting Started

You'll need to have the following installed in your machine:
* GNU Make (for windows tested with GNU make v4.3)
* g++ that supports C++14 (for windows tested with 8.1.0)
* git

## Building Application
You can build the console application via Visual Studio IDE (see ide_project/vs) or via makefile.
Build application by invoking `make` command in root.

## Running Application
#### Windows
`<root>\ToyRobot.exe`
#### Linux
`<root>/ToyRobot.out`

## Building Tests
You can run the unit tests via Visual Studio IDE (see ide_project/vs) or via makefile.
Build tests by invoking:
```
git submodule update --init --recursive
make tests
```

## Running Tests
#### Windows
`<root>\test_ToyRobot.exe`
#### Linux
`<root>/test_ToyRobot.out`

### Notes
* When using Visual Studio IDE, download package `Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn.1.8.1.5`

### Todo
* Solution to workaround for _strdup (in util.cpp)
* Add automated integration test for console application built
