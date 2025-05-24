cmake_minimum_required(VERSION 3.16)
project(FrtosSim)

add_subdirectory(json)
include_directories(json/include)

add_subdirectory(common)
include_directories(common)

add_subdirectory(config)
include_directories(config)

add_subdirectory(logging)
include_directories(logging)

add_subdirectory(thread)
include_directories(thread)

add_subdirectory(task)
include_directories(task)

set(SOURCE_FILES 
    main.cpp )

add_compile_definitions(
    TEST_DATA_DIR="/home/vboxuser/dev/dipl/test/data")

add_executable(FrtosSim ${SOURCE_FILES})
target_link_libraries(
    FrtosSim 
    common 
    config 
    logging 
    thread 
    task 
    nlohmann_json::nlohmann_json)
install(TARGETS FrtosSim DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
