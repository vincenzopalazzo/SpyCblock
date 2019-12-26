# Build SpyCblock

At the moment the only method for build SpyCblock is with scripts contained inside the directory called **installer** or command line.
I hope to implement the complete installer with [CMake](https://cmake.org/) in the future.

PS: SpyCblock was developed for work on Linux OS (based Ubuntu/Debian), I think work on the OSX but I don't think work on Windows ("I hope" only for the moment).

PS: unfortunately, the script does not have the capacity to aborted after error; so you pay attention to the console.

# Scripts description

Inside the directory **installer** exist some script for different type system build, like:

- **compile.sh**: This script is for the first operation build, it will call the dependences.sh and update-submodule.sh; compile.sh create the new directory inside the root project called **build**;
- **compile-without-dependence.sh**: this script suppose that the dependencies are installed and it was created the build directory; when running the script you create the executable with the executable;
- **compile-test.sh**: this script supposes that the dependences are install corrected and it will create the test inside the directory **test/build/**. For run the test you have the need to the directory test structure, you can download it [here](#todo) or if you want to use the onionShare you can download it [here](#todo);
- **dependences.sh**: You can use this script to install the dependence, if it doesn't work see [here](#todo) to install dependence manually
- **update-submodule.sh**: you can use this script for initialized the git submodules.

## Build from the script

If you compile for the first time SpyCblock you can run the command `./compile.sh`, if the command runs without error, you can find the binary inside the build directory.

After this, you can jump to the [configure section](#TODO)

If you want recompiling only the binary you can run the script `./compile-without-dependence.sh`

## Build SpyCblock tests for scripts

If you want to compile the SpyCblock test you can run the `./compile.sh` and if it ran without error you can run also the command `./compile-test.sh`; if the compile-test.sh run without error you have needed the structure of the directory for the test, you can find it [here](#TODO) or on [OnionShare](#TODO)

After this, you can jump to the [configure section](#TODO)

# Build from the command line

If the script doesn't work and you can use the console for installing it (**The script is tested only on Linux (based on Ubuntu/Debian)**)

##  Dependencies for the develop

- `sudo get update && apt-get install build-essential -y`
- `sudo apt-get install zlib1g-dev -y`
- `sudo apt-get install libncurses-dev -y`
- `sudo apt install cmake -y`
- run the script `./update-submodule.sh`

## External dependence

You can use the original guide to install the single project

- [GLog](https://github.com/google/glog/blob/master/cmake/INSTALL.md)
- [RapidJSON](https://github.com/Tencent/rapidjson)
- [libjson-rpc-cpp](https://github.com/cinemast/libjson-rpc-cpp)
- [Bitcoin-api-cpp](https://github.com/minium/bitcoin-api-cpp)

If you want to compile the test, you can install the Gtest dependences

- [Gtest](https://github.com/google/googletest)

## Compile SpyCblock

- `make build && cd build`
- `cmake ...`
- `make`
- `cd .. && cp conf.properties build && cp conf-rpc.properties build && cd build`
- **./SpyCBlock**

## Compile SpyCblockTest

- `cd test && mkdir build && cd build && cmake .. && make`
- **./SpyCBlockTest**
