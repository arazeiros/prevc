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
 * [LLVM 7](http://llvm.org/)

Project also depends on the `clang` compiler that have to be installed
and present in the path of the shell.

On Ubuntu 18.10 you can install these by typing command:

``` console
$ sudo apt install libutfcpp-dev llvm-7-dev clang
```

## License

`prevc` is provided under the MIT license. See [LICENSE](LICENSE).
