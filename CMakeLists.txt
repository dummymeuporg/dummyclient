cmake_minimum_required(VERSION 3.10.0)
project(dummyclient)
include_directories(include vendor/libdummy/include)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

add_definitions(-D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING)

add_subdirectory("vendor/libdummy")

find_package(SFML COMPONENTS graphics audio REQUIRED)
find_package(Boost 1.69 COMPONENTS date_time REQUIRED)
find_package(Lua 5.1 REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

macro(GroupSources curdir)
    file(
        GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
        ${PROJECT_SOURCE_DIR}/${curdir}/*
    )
    foreach(child ${children})
        if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            GroupSources(${curdir}/${child})
        else()
            string(REPLACE "/" "\\" groupname ${curdir})
            source_group(
                ${groupname}
                FILES
                ${PROJECT_SOURCE_DIR}/${curdir}/${child}
            )
        endif()
    endforeach()
endmacro()

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

GroupSources(include)
GroupSources(src)

set(CLIENT_LINK_LIBRARIES
    ${Boost_LIBRARIES}
    sfml-audio
    sfml-graphics
    sfml-network
    sfml-system
    dummy
    ${LUA_LIBRARY}
)

# On Linux, explicitly pass libraries.
if (UNIX)
    set(CLIENT_LINK_LIBRARIES
        ${CLIENT_LINK_LIBRARIES}
        pthread
    )
    add_executable(dummyclient ${SOURCES} ${HEADERS})
endif (UNIX)

IF (WIN32)
    add_executable(dummyclient WIN32 ${SOURCES} ${HEADERS})
    SET_TARGET_PROPERTIES (dummyclient
        PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:console /NODEFAULTLIB:library"
    )
    SET_TARGET_PROPERTIES (dummyclient
        PROPERTIES LINK_FLAGS_RELEASE
        "/SUBSYSTEM:windows /ENTRY:mainCRTStartup /NODEFAULTLIB:library"
    )
    SET_TARGET_PROPERTIES (dummyclient
        PROPERTIES LINK_FLAGS_MINSIZEREL
        "/SUBSYSTEM:windows /ENTRY:mainCRTStartup /NODEFAULTLIB:library"
    )
    SET_TARGET_PROPERTIES (dummyclient
        PROPERTIES LINK_FLAGS_RELWITHDEBINFO
        "/SUBSYSTEM:windows /ENTRY:mainCRTStartup /NODEFAULTLIB:library"
    )

    # On Windows, need to specify Boost’s lib dir. Sick.
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        target_link_directories(dummyclient
            PUBLIC
            ${Boost_LIBRARY_DIR_DEBUG}
        )
    endif (CMAKE_BUILD_TYPE MATCHES Debug)

    if (CMAKE_BUILD_TYPE MATCHES Release)
        target_link_directories(dummyclient
            PUBLIC
            ${Boost_LIBRARY_DIR_RELEASE}
        )
    endif (CMAKE_BUILD_TYPE MATCHES Release)
ENDIF (WIN32)


target_include_directories(dummyclient
    PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${LUA_INCLUDE_DIR}
)

target_link_libraries(dummyclient
    ${CLIENT_LINK_LIBRARIES}
)
