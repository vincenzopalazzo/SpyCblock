# Build SpyCBlock

For the moment the only method for install is with scripts conteined inside the directory called **installer** or comand line.
I hope to implemente the complete installer with [CMake](https://cmake.org/) in the future.

## Build from script

Inside the directory **installer** exist some script for different type system build, like:

- **compile.sh**: This script is for the first operation build, it will call the dependences.sh and update-submodule.sh; compile.sh create the new directory inside the root project called **build**;
- **compile-without-dependence.sh**: this script suppone that the dependences are installed and it creare the build directory with the executible;
- **compile-test.sh**: this script suppone that the dependences are install corrected and create the test inside the directory **test/build/**. For run the test you have need to the directory test structure, you can download it [here](#todo) or if you want use the onionShare you can download it [here](#todo);
- **dependences.sh**: You can use this script for install the dependence, if it don't work see [here](#todo) for install dependence manualy
- **update-submodule.sh**: you can used this script for init the git submodule.



## Build from comand line

_TODO_
