# 0 Greetings
Welcome to the installation!

**Contents**

1 Requirements
2 Installation
3 Realtime check with stoat
4 Running
5 Debugging

# 1 Requirements
You will need the following libraries, headers and tools:
  * at least g++ 4.8 or clang 3.3
  * pthreads
  * [cmake](http://www.cmake.org/)

# 2 Installation of the commandline interface
In this directory, type:
```sh
mkdir build
cd build
# for a release build using clang (suggested), where /path/to/zynaddsubfx is
# the binary executable for zynaddsubfx
cmake -DCOMPILER=clang \
      -DCMAKE_BUILD_TYPE=Release \
      ..
```  

# 3 Realtime check with stoat
Make sure [stoat](https://github.com/fundamental/stoat) is (root-)installed on your disk.

Instead of using the cmake code from above, use
```sh
cmake -DCOMPILER=stoat ..
```

Then, run
```sh
make stoat2
```

The output should prompt a total of 0 errors.

# 4 Running
You can execute tests now. For example, TODO...
```sh
  ./src/TODO <arguments>
```

# 5 Debugging
TODO

