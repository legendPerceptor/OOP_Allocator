<<<<<<< HEAD
cmake_minimum_required(VERSION 3.5)
project(OOP_Allocator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set (CMAKE_CXX_FLAGS " -pthread " )
=======
cmake_minimum_required(VERSION 3.9)
project(OOP_Allocator)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
>>>>>>> 34264074337c7fa91f6c2fb2387ce7bb200d11e3

include_directories(include)

set(SOURCE_CODE
        source/Fault.cpp include/Fault.h
        source/Allocator.cpp include/Allocator.h
        source/xallocator.cpp include/xallocator.h
        source/h_allocator.cpp include/h_allocator.h
        source/hlist.cpp include/hlist.h
        )

<<<<<<< HEAD
#add_library(hstring source/hstring.cpp include/hstring.h)
add_library(hlist source/hlist.cpp include/hlist.h)
target_link_libraries(hlist h_allocator)

add_executable(OOP_Allocator main.cpp)
target_link_libraries(OOP_Allocator hlist)
=======
add_executable(Main main.cpp ${SOURCE_CODE})


add_executable(Test test.cpp ${SOURCE_CODE})
>>>>>>> 34264074337c7fa91f6c2fb2387ce7bb200d11e3
