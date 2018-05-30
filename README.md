# prevc

A compiler for the Prev programming language.

## Building

The project uses CMake as the build system. To build the library perform
those commands in the project's root folder:

``` console
$ mkdir cmake-build
$ cd cmake-build
$ cmake ..
$ make
```

### Dependencies

Project depend on some third-party libraries:

 * [UTF8-CPP](http://utfcpp.sourceforge.net/)
 * [LLVM 6](http://llvm.org/)

Project also depends on the `clang` compiler that have to be installed
and present in the path of the shell.

On OpenSUSE you can install these by typing command:

``` console
# zypper in utfcpp-devel llvm6-devel clang
```


