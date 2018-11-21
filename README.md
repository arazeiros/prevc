# prevc

A compiler for the Prev programming language. `prevc` is written in C++17 using
[LLVM](http://llvm.org/) as backend. Currently the implemented Prev standard is
`slivnik17` described in [this](doc/specification.pdf) specification.

## Usage

To compile and emit the binary executable:

``` console
$ prevc main.prev
$ ./main
```

To compile and emit the LLVM IR code (.ll extension):

``` console
$ prevc --out-llvm-ir main.prev
```

For some extra help:

``` console
$ prevc --help
```

## Building

The project uses [CMake](https://cmake.org/) as the build system. To build the
library perform those commands in the project's root folder:

``` console
$ mkdir cmake-build
$ cd cmake-build
$ cmake ..
$ make
```

Building also depends on Python 3 (for some source code generation), so make sure that
`python3` is installed and present in the path of the shell.

### Dependencies

Project depend on some third-party libraries:
 * [UTF8-CPP](http://utfcpp.sourceforge.net/)
 * [LLVM 7](http://llvm.org/) (not backward compatible with previous LLVM versions)

`prevc` uses `clang` compiler at runtime (for linking with the C standard library), so 
make sure that `clang` is installed and present in the path of the shell.

On Ubuntu 18.10 you can install these by typing command:

``` console
$ sudo apt install libutfcpp-dev llvm-7-dev clang
```

## License

`prevc` is provided under the MIT license. See [LICENSE](LICENSE).
