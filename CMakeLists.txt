cmake_minimum_required(VERSION 3.5)
project(OOP_Allocator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set (CMAKE_CXX_FLAGS " -pthread " )

include_directories(include)

add_library(Fault source/Fault.cpp include/Fault.h)
add_library(Allocator source/Allocator.cpp include/Allocator.h)
add_library(xallocator source/xallocator.cpp include/xallocator.h)
target_link_libraries(xallocator Allocator Fault)
add_library(h_allocator source/h_allocator.cpp include/h_allocator.h)
target_link_libraries(h_allocator xallocator)

#add_library(hstring source/hstring.cpp include/hstring.h)
add_library(hlist source/hlist.cpp include/hlist.h)
target_link_libraries(hlist h_allocator)

add_executable(OOP_Allocator main.cpp)
target_link_libraries(OOP_Allocator hlist)
