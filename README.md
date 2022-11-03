# cpp_container

[Vector (a sequence container that encapsulates dynamic size arrays) implementation.](https://github.com/kuznetsov-m/cpp_container/blob/master/vector.cpp)

The project uses [GoogleTest](http://google.github.io/googletest/) framework. Running tests is automated with **GitHub Actions**.

## How to build
```
cd cpp_container
cmake -S. -Bbuild
cmake --build build
```

## Running the tests
```
cd build
ctest
```

# Links
- other example: https://github.com/StrongUzumaki/FT_Containers/blob/master/vector/Vector.hpp