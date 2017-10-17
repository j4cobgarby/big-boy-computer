cmake_minimum_required(VERSION 2.0)

project(big-boy-computer)

# Add your own link directories (if not standard) here.
link_directories("C:\\mingw64-gcc6.1.0\\lib")
include_directories("C:\\mingw64-gcc6.1.0\\include")

SET(CMAKE_EXE_LINKER_FLAGS "-pthread -lsfml-graphics -lsfml-window -lsfml-system")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++14 -pedantic -Wall -Wextra -Wno-unused-parameter")

file(GLOB all_src "*.hpp" "*.cpp")

add_executable(bigboy ${all_src})

target_link_libraries(bigboy sfml-graphics sfml-window sfml-system sfml-network)
