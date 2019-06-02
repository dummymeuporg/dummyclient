cmake_minimum_required(VERSION 3.10.0)
project(dummyclient)
include_directories(include vendor/libdummy/include)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
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

source_group("src" FILES ${HEADERS} RELATIVE ${CMAKE_CURRENT_SOURCE_DIR})
source_group("include" FILES ${SOURCES} RELATIVE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(dummyclient WIN32 ${SOURCES} ${HEADERS})

set(CLIENT_LINK_LIBRARIES
    ${Boost_LIBRARIES}
    sfml-graphics
    sfml-network
    sfml-system
    dummy
)

# On Linux, explicitly pass libraries.
if (UNIX)
    set(CLIENT_LINK_LIBRARIES
        ${CLIENT_LINK_LIBRARIES}
        boost_filesystem
        stdc++fs
    )
    add_executable(dummyclient WIN32 ${SOURCES} ${HEADERS})
endif (UNIX)

IF (WIN32)
    SET_TARGET_PROPERTIES (dummyclient
        PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:console"
    )
    SET_TARGET_PROPERTIES (dummyclient
        PROPERTIES LINK_FLAGS_RELEASE
        "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
    )
    SET_TARGET_PROPERTIES (dummyclient
        PROPERTIES LINK_FLAGS_MINSIZEREL
        "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
    )
    SET_TARGET_PROPERTIES (dummyclient
        PROPERTIES LINK_FLAGS_RELWITHDEBINFO
        "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
    )
ENDIF (WIN32)


target_include_directories(dummyclient PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(dummyclient
    ${CLIENT_LINK_LIBRARIES}
)
