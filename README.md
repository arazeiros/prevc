# prevc

A compiler for the Prev programming language. `prevc` is written in C++17 using
[LLVM](http://llvm.org/) as backend. Currently the implemented Prev standard is
`slivnik17` described in [this](doc/specification.pdf) specification.

## Usage

To compile and emit the binary executable:

```bash
prevc main.prev
./main
```

To compile and emit the LLVM IR code (.ll extension):

```bash
prevc --out-llvm-ir main.prev
```

For some extra help:

```bash
prevc --help
```

## Building

On Ubuntu 22.04 all dependencies can be installed with:

```bash
sudo apt install g++ cmake python3 llvm-13 libzip-dev libutfcpp-dev
```

Then to build the `prevc` executable perform these commands in the project's root folder:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j $(nproc --all)
```

## License

`prevc` is provided under the MIT license. See [LICENSE](LICENSE).
