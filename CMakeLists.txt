cmake_minimum_required(VERSION 3.31)
project(simple_pong C)

set(CMAKE_C_STANDARD 99)

# Include the command that downloads libraries
include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    # setup the declare
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

# add raylib support
set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
    message(STATUS "Getting ${LIB1} from Github")
    include_dependency(${LIB1} https://github.com/raysan5/raylib.git 5.5)
else()
    message(STATUS "Using local ${LIB1}")
endif()

add_executable(simple_pong src/main.c
        src/game/game.c
        src/game/game.h
        src/utils/constants.h
        src/utils/types.h
        src/game/paddle.h
        src/game/paddle.c
        src/game/ball.h
        src/game/ball.c
        src/audio/audio_manager.c
        src/audio/audio_manager.h
        src/game/particles_system.c
        src/game/particles_system.h)

# set the include directory
target_include_directories(simple_pong PRIVATE ${raylib_INCLUDE_DIRS})

# link all libraries to the project
target_link_libraries(simple_pong PRIVATE ${LIB1})