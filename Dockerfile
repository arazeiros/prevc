#########################
# base image used for creating the `build` and then final image
FROM ubuntu:22.04 as base

# setting the default warking directory
WORKDIR /prevc/

# installing `binutils` (for `ld`) and C development headers/libs
RUN apt-get update
RUN apt-get install -y --no-install-recommends binutils libc-dev

# removing the unnecessary lists of packages (space optimization)
RUN rm -rf /var/lib/apt/lists/*

#########################
# the `build` image builds the `prevc` executable
FROM base as build

# installing the `build` dependencies
RUN apt-get update
RUN apt-get install -y g++ cmake llvm-13 libzip-dev libutfcpp-dev

# copying the source files needed for the compilation
COPY include/ include/
COPY script/ script/
COPY src/ src/
COPY CMakeLists.txt CMakeLists.txt

# configuration of the compilation files via `cmake`
RUN mkdir build
WORKDIR /prevc/build/
RUN cmake -DCMAKE_BUILD_TYPE=Release ..

# compilation of `prevc`
RUN make -j $(nproc --all)

#########################
# the final image containing the `prevc` executable
FROM base

# copying `prevc` executable from the `build` image
COPY --from=build /prevc/build/prevc /usr/local/bin/prevc

# just executing `prevc` by default
CMD ["/usr/local/bin/prevc"]
