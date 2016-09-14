# Genetic Algorithm for solving the Rubik's Cube

C++ GA implementation for solving Rubik's Cube. It solves the 3x3 cube but was designed to optimize solutions for cubes of any size.

### Dependencies

* [CMake](https://cmake.org/)
* [Google Test](https://github.com/google/googletest)
* [Gnuplot](http://www.gnuplot.info/)
* [g++-5](https://gcc.gnu.org/gcc-5/changes.html)

### Build Instructions

#### For Ubuntu 14.04 x64:

* Install Cmake:

```
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:george-edison55/cmake-3.x
sudo apt-get update
sudo apt-get install cmake
```

* Install Gnuplot:

```
sudo aplt-get install gnuplot
```

* Install g++-5

```
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-5 g++-5
```

* Install Google Test

```
sudo apt-get install libgtest-dev
cd /usr/src/gtest
sudo mkdir build_make && cd build_make
sudo CC=gcc-5 CXX=g++-5 cmake -DCMAKE_BUILD_TYPE=RELEASE /usr/src/gtest/
sudo make
sudo mv libg* /usr/lib/
```

* Build GA

```
mkdir build_make && mkdir deploy && cd build_make
sudo CC=gcc-5 CXX=g++-5 cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=../deploy ../
make && make install
```

The compiled GA should be within deploy folder.

To build the GA using static seed for the random number generator (for test purposes), just use the `-DUSE_STATIC_SEED=ON` option on the cmake configuration line.

### Documentation

There is a report file in the doc/ folder that contains a detailed description (in brazilian portuguese) about the GA.
