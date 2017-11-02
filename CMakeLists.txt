cmake_minimum_required(VERSION 2.8)

project(Serial)
#LINK_DIRECTORIES("/usr/lib/x86_64-linux-gnu/")
add_executable(${PROJECT_NAME} "main.cpp")
TARGET_LINK_LIBRARIES(Serial serial pthread)

