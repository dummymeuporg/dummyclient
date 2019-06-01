cmake_minimum_required(VERSION 3.10.0)
project(dummyclient)
include_directories(include vendor/libdummy/include)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
	-L${CMAKE_CURRENT_SOURCE_DIR}/vendor/libdummy/build")

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

add_subdirectory("vendor/libdummy")

find_package(SFML COMPONENTS graphics audio REQUIRED)
find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

add_executable(dummyclient ${SOURCES} ${HEADERS})

target_include_directories(dummyclient PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(dummyclient
    ${Boost_LIBRARIES}
    sfml-graphics
    sfml-network
    sfml-system
    sfml-window
    dummy
)
