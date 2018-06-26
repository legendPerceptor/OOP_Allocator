cmake_minimum_required(VERSION 3.10)
project(OOP_Allocator)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

include_directories(include)

set(SOURCE_CODE
        source/Fault.cpp include/Fault.h
        source/Allocator.cpp include/Allocator.h
        source/xallocator.cpp include/xallocator.h
        source/h_allocator.cpp include/h_allocator.h
        source/hlist.cpp include/hlist.h
        )

add_executable(Main main.cpp ${SOURCE_CODE})


add_executable(Test test.cpp ${SOURCE_CODE})
