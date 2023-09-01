include(AddLLVM) 是取找目录中AddLLVM.cmake这个文件

CMAKE_CURRENT_SOURCE_DIR 表示根目录的cmake文件路径

ADD_DEFINITIONS是CMake中的一个命令，用于向工程添加编译定义。编译定义是在编译时期指定的一些预定义宏或者变量，


include_directories(SYSTEM /usr/include) # 添加系统级别的头文件搜索路径

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99") # enable C99 standard
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # enable C++11 standard