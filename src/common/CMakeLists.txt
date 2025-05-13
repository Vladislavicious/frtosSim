cmake_minimum_required(VERSION 3.16)
project(common C CXX)

set(SOURCE_FILES
    common.h
    common.cpp
    fileWork.h
    fileWork.cpp
    time_sv.h
    time_sv.cpp
    initializable.h
    initializable.cpp
)

add_library(common SHARED STATIC ${SOURCE_FILES})

install(TARGETS common DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES 
    common.h 
    fileWork.h
    time_sv.h 
    initializable.h 
    DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
