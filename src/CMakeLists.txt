cmake_minimum_required(VERSION 3.16)
project(FrtosSim)

add_subdirectory(json)
include_directories(json/include)

add_subdirectory(common)
include_directories(common)

add_subdirectory(config)
include_directories(config)


set(SOURCE_FILES 
    main.cpp )

add_executable(FrtosSim ${SOURCE_FILES})
target_link_libraries(FrtosSim common config nlohmann_json::nlohmann_json)
install(TARGETS FrtosSim DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
