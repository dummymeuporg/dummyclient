cmake_minimum_required(VERSION 3.10.0)
project(dummyclient)
include_directories(include vendor/libdummy/include)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
	-L${CMAKE_CURRENT_SOURCE_DIR}/vendor/libdummy/build")

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

add_executable(dummyclient ${SOURCES} ${HEADERS})


target_link_libraries(dummyclient
    boost_system
    sfml-graphics
    sfml-network
    sfml-system
    sfml-window
    dummy
    stdc++fs
)
