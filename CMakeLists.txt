cmake_minimum_required(VERSION 2.8)

project(stlab C CXX)


set(CMAKE_SKIP_RPATH OFF)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")  
  #set(CMAKE_CXX_FLAGS "-g -Wall -O3 -std=c++14 -fsanitize=thread -fexceptions -D_GLIBCXX_USE_CXX11_ABI=0")
  if (APPLE)
    set(CMAKE_CXX_FLAGS "-O3 -g -Wall -std=c++14 -fexceptions -ftemplate-backtrace-limit=0 -D_GLIBCXX_USE_CXX11_ABI=0 -DAPPLE")
  else()
    set(CMAKE_CXX_FLAGS "-O3 -g -Wall -std=c++14 -fexceptions -ftemplate-backtrace-limit=0 -D_GLIBCXX_USE_CXX11_ABI=0")
  endif()
  set(CMAKE_LINK_FLAGS "-pthreads")
  SET (CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS_INIT} $ENV{LDFLAGS})
endif()

set (Boost_MULTITHREADED ON) 

if(WIN32)
  add_definitions(-D_WIN32_WINNT=0x0601)
  #add_definitions( -DBOOST_ALL_NO_LIB )
  #add_definitions( -DBOOST_ALL_DYN_LINK )
  set (Boost_USE_STATIC_LIBS ON)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
else()
  set (Boost_USE_STATIC_LIBS ON)
endif(WIN32)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    set(CONAN_SYSTEM_INCLUDES ON)
    conan_basic_setup()
else()
    if(MSVC)
        set(Boost_USE_STATIC_LIBS TRUE)
    endif()
    
    find_package(Boost 1.60.0 )
    
    if(UNIX)
        add_definitions("-DBOOST_TEST_DYN_LINK")
    endif()
    include_directories(SYSTEM ${Boost_INCLUDE_DIR})
    link_directories(${Boost_LIBRARY_DIR})
endif()

set (Boost_MULTITHREADED ON) 

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

find_package( Threads )

if(CMAKE_USE_PTHREADS_INIT)
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")
endif()

include_directories(.)
include_directories(stlab)
include_directories(nana/include)

add_subdirectory(stlab)
add_subdirectory(nana)
add_subdirectory(Exercise01)
add_subdirectory(Exercise02)
add_subdirectory(Exercise03)
add_subdirectory(Exercise04)
