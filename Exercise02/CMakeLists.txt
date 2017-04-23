PROJECT(Exercise02)

set(SOURCE
  #main.cpp
  solution.cpp
)

set(HEADERS
)

add_executable(Exercise02 ${SOURCE} ${HEADERS})

include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(
        Exercise02
    ${CMAKE_THREAD_LIBS_INIT})

set_property(TARGET Exercise02 PROPERTY CXX_STANDARD 14)
set_property(TARGET Exercise02 PROPERTY CXX_STANDARD_REQUIRED ON)
