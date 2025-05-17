cmake_minimum_required(VERSION 3.16)
project(task C CXX)

set(SOURCE_FILES
    buildTask.h
    buildTask.cpp
    taskInterface.h
    taskInterface.cpp
    myPipe.h
)

add_library(task SHARED STATIC ${SOURCE_FILES})

install(TARGETS task DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES 
    taskInterface.h
    buildTask.h 
    myPipe.h
    DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
