cmake_minimum_required(VERSION 3.16)
project(logging C CXX)

set(SOURCE_FILES
    logger.h
    logger.cpp
    loggable.h
    loggable.cpp
)

add_library(logging SHARED STATIC ${SOURCE_FILES})

install(TARGETS logging DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES 
    logger.h 
    loggable.h 
    DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
