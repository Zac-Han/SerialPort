cmake_minimum_required(VERSION 2.8)

project(SerialPort)
file(GLOB SRCS *.cpp *.h)
add_executable(${PROJECT_NAME} ${SRCS})
TARGET_LINK_LIBRARIES(SerialPort serial pthread)

