PROJECT(Exercise01)

set(SOURCE
  main.cpp
  #solution.cpp
)

set(HEADERS
)

add_executable(Exercise01 ${SOURCE} ${HEADERS})

include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(
        Exercise01
    ${CMAKE_THREAD_LIBS_INIT}
    nana)

set_property(TARGET Exercise01 PROPERTY CXX_STANDARD 14)
set_property(TARGET Exercise01 PROPERTY CXX_STANDARD_REQUIRED ON)
