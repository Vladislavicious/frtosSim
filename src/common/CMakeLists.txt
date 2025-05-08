cmake_minimum_required(VERSION 3.16)
project(common C CXX)

set(SOURCE_FILES
    common.h
    common.cpp
    time_sv.h
    time_sv.cpp
)

add_library(common SHARED STATIC ${SOURCE_FILES})

install(TARGETS common DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES common.h time_sv.h DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
