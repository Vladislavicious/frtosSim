cmake_minimum_required(VERSION 3.16)
project(task C CXX)

set(SOURCE_FILES
    taskInterface.h
    taskInterface.cpp
)

add_library(task SHARED STATIC ${SOURCE_FILES})

install(TARGETS task DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES 
    taskInterface.h 
    DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
