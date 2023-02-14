# generate boost library on windows
download boost from https://www.boost.org/users/history/
```
cd \boost_1_81_0\tools\build\src\engine
.\build.bat gcc

cp b2.exe bjam.exe \boost_1_81_0
.\b2.exe toolset=gcc
```
staging directory was generated. The can run g++ to build program.

# build
g++ -o main -I D:\\Projects\\boost\\boost_1_81_0 .\hello_world.cpp

# Add include to vscode
Ctrl+Alt+P open C/C++ edit configuration, add boost/boost_1_81_0 path to includePath, like the following:
```
 "includePath": [
                "${workspaceFolder}/**",
                "D:/Projects/leveldb/include",
                "D:/Projects/boost/boost_1_81_0"
            ],
```            

# reference
[Win10下 VScode+boost使用 需要用visual studio]https://blog.csdn.net/dengdui6364/article/details/126413578
[参考编译staging ](https://www.cnblogs.com/Fight-go/p/15812452.html)