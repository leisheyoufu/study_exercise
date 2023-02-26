cmake_minimum_required(VERSION 3.0.0)
project(rpathTest)

#设置可执行文件输出
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置库文件输出
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/lib)
#生成共享库
add_library(hello SHARED hello.cpp)
#设置RPATH
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
#生成可执行文件
add_executable(rpathTest test.cpp)
#设置依赖的库文件
target_link_libraries(rpathTest hello)
#设置RPATH路径
set_target_properties(rpathTest PROPERTIES INSTALL_RPATH "$ORIGIN/lib")
