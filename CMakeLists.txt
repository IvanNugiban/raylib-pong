cmake_minimum_required(VERSION 3.0)
project(raylib_pong C CXX)

set(CMAKE_CXX_STANDARD 17)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
add_executable(${PROJECT_NAME} WIN32  src/main.cpp "src/player.h" "src/controlledplayer.h" "src/controlledplayer.cpp" "src/player.cpp" "src/constants.h" "src/helpers.cpp" "src/ball.h" "src/ball.cpp" "src/entity.h"  "src/aiplayer.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
