cmake_minimum_required(VERSION 3.10.0)
project(dummyclient)
include_directories(include vendor/libdummy/include)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
	-L${CMAKE_CURRENT_SOURCE_DIR}/vendor/libdummy/build")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall")

add_executable(dummyclient
	src/main.cpp
    src/client.cpp
    src/credentials.cpp
    src/game.cpp
    src/client_state/state.cpp
    src/client_state/initial_state.cpp
    src/client_state/receive_characters_state.cpp
    src/screen/screen.cpp
    src/screen/select_character_screen.cpp
    src/model/model.cpp
    src/model/characters_list_model.cpp
)

target_link_libraries(dummyclient
    boost_system
	sfml-graphics
    sfml-network
	sfml-system
	sfml-window
    dummy
)
