cmake_minimum_required(VERSION 3.16)
project(thread C CXX)

set(SOURCE_FILES
    threadInterface.h
    threadInterface.cpp
)

add_library(thread SHARED STATIC ${SOURCE_FILES})

install(TARGETS thread DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES 
    threadInterface.h 
    DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
