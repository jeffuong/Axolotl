# Axolotl
<img align="left" src="https://github.com/jeffuong/Notefad/blob/master/src/imgs/readmeicon.png" alt="Axolotl" height="100px"/>
This repository is a C++ project trying to recreate a cross-platform text editor similar to Sublime/Visual Studio Code using the Qt 5 library.

The Axolotl icon was provided by [Kisspng](https://www.kisspng.com) and edited through Gimp.

![Demo](https://user-images.githubusercontent.com/25240780/52088241-381ca400-2560-11e9-9e62-98f9d2b570f1.gif)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine

### Prerequisites

```
git
CMake 3.1 or above
Qt 5
```

### Building

We use CMake to build the project. Currently right now the architecture we're building with is x64.
Generally we make a seperate directory and make sure cmake builds to this directory. For example
when build with cmake installed and Qt 5 installed
```
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=C:/PATH/TO/YOUR/QT/COMPILER_BUILD
make
```

Make sure to specify where the Qt install directory is in the CMAKE_PREFIX_PATH flag