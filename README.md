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

## Docker

A Docker image, with a pre-compiled `prevc` executable, is available on [Docker Hub](https://hub.docker.com/r/pintarj/prevc). You can download it with:
```bash
docker pull pintarj/prevc
```

To compile a local `.prev` file (for example `demo/sudoku.prev`), mounting a folder in a Docker container, run:
```bash
docker run --rm --volume $(pwd):/prevc pintarj/prevc /usr/local/bin/prevc demo/sudoku.prev
```

**NOTE:** The produced executable will require, on execution, a version of [GLIBC](https://www.gnu.org/software/libc/) installed on the local machine _compatible_ with the version with which it was compiled in the Docker container.

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
