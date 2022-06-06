cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

project(olc)

find_package(X11 REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(SDL2 REQUIRED)

add_library(utils-lib STATIC
   utils.cc)
target_link_libraries(utils-lib X11::X11)

macro(add_olc_executable NAME)
   add_executable(${NAME} "${NAME}.cc")
   target_link_libraries(${NAME} X11::X11 Threads::Threads OpenGL::GL PNG::PNG stdc++fs)
endmacro()

macro(add_sdl_executable NAME)
   add_executable(${NAME} "${NAME}.cc")
   target_include_directories(${NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
   target_link_libraries(${NAME} ${SDL2_LIBRARIES})
endmacro()


add_sdl_executable(sound_synthesizer)
target_link_libraries(sound_synthesizer utils-lib)