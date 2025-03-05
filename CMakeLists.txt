cmake_minimum_required(VERSION 3.30)
project(xbox_sender C)

set(CMAKE_C_STANDARD 23)

add_executable(xbox_sender src/main.c
        src/socket-client.c
        src/socket-client.h
        src/xbox.c
        src/xbox.h)

target_link_libraries(${PROJECT_NAME} evdev)
