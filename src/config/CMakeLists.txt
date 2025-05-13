cmake_minimum_required(VERSION 3.16)
project(config C CXX)

set(SOURCE_FILES
    config.h
    config.cpp
    loggerConfig.h
    loggerConfig.cpp
    buildConfig.h
    buildConfig.cpp
    simulatorConfig.h
    simulatorConfig.cpp
)

add_library(config SHARED STATIC ${SOURCE_FILES})
target_link_libraries(config PRIVATE common) # link common agains config

install(TARGETS config DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES 
    config.h 
    loggerConfig.h
    buildConfig.h
    simulatorConfig.h
        DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
