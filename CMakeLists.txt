cmake_minimum_required(VERSION 3.10)
project(Webtext)


set(CMAKE_CXX_STANDARD 11)


find_package(PkgConfig REQUIRED)
pkg_check_modules(MICROHTTPD REQUIRED libmicrohttpd)

# 添加可执行文件
add_executable(Webtext main.cpp)

# 链接 libmicrohttpd
target_include_directories(Webtext PRIVATE ${MICROHTTPD_INCLUDE_DIRS})
target_link_libraries(Webtext ${MICROHTTPD_LIBRARIES})
target_compile_options(Webtext PRIVATE ${MICROHTTPD_CFLAGS_OTHER})