cmake_minimum_required(VERSION 3.21)
project(server_chat)

set(CMAKE_CXX_STANDARD 17)

add_executable(server_chat
        main.cpp
        server.cpp server.hpp
        client.cpp client.hpp)
