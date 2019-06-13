# Axolotl
<img align="left" src="https://github.com/jeffuong/Notefad/blob/master/src/imgs/readmeicon.png" alt="Axolotl" height="100px"/>

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/bf85c7adebd24d3d8499b108f23b6cbe)](https://app.codacy.com/app/Erctrn/Axolotl?utm_source=github.com&utm_medium=referral&utm_content=jeffuong/Axolotl&utm_campaign=Badge_Grade_Settings)
[![Build Status](http://54.153.72.145/job/Axolotl/job/master/badge/icon)](http://54.153.72.145/job/Axolotl/job/master/)

This repository is a C++ project trying to recreate a cross-platform text editor similar to Sublime/Visual Studio Code using the Qt 5 library.

The Axolotl icon was provided by [Kisspng](https://www.kisspng.com) and edited through Gimp.

![Demo](https://user-images.githubusercontent.com/25240780/59009810-f2106f00-87e3-11e9-8d7d-106c6c87e01c.gif)

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