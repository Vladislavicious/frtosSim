cmake_minimum_required(VERSION 3.16)
project(task C CXX)

set(SOURCE_FILES
    buildTask.h
    buildTask.cpp
    taskInterface.h
    taskInterface.cpp
    myProcess.h
    myProcess.cpp
    simulatorTask.h
    simulatorTask.cpp
)

add_library(task SHARED STATIC ${SOURCE_FILES})

install(TARGETS task DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES 
    taskInterface.h
    buildTask.h 
    myProcess.h
    simulatorTask.h
    DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
