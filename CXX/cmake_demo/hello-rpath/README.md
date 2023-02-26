## build lib and bin
g++ -shared  -o libhello.so hello.cpp
g++ -o test test.cpp -lhello -L ./  # windows mingw can not work, linux is fine


./test
```
./test: error while loading shared libraries: libhello.so: cannot open shared object file: No such file or directory
```

readelf -d test
ldd test

## rpath
g++ -o test test.cpp -lhello -L ./ -Wl,-rpath=./

mkdir build
cd build
cmake ..