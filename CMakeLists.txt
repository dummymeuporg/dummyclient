cmake_minimum_required(VERSION 3.10.0)
project(dummyclient)
include_directories(include)

add_executable(dummyclient
	src/main.cpp
    src/client.cpp
    src/credentials.cpp
    src/client_state/state.cpp
    src/client_state/initial_state.cpp
)

target_link_libraries(dummyclient
    boost_system
	sfml-graphics
    sfml-network
	sfml-system
	sfml-window
)
