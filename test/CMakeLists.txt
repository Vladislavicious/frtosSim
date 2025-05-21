cmake_minimum_required(VERSION 3.16)
project(my_tests)

add_subdirectory(lib/googletest)

include_directories(../src/common)
include_directories(../src/config)
include_directories(../src/logging)
include_directories(../src/include)
include_directories(../src/task)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

set(SOURCE_FILES 
    main.cpp 
    src/time_sv_tests.cpp
    src/common_tests.cpp
    src/initializable_tests.cpp
    src/json_tests.cpp
    src/config_tests.cpp
    src/loggerConfig_tests.cpp
    src/buildConfig_tests.cpp
    src/logger_tests.cpp
    src/conceptTask_tests.cpp
    src/buildTask_tests.cpp
    src/connectionTypes_tests.cpp
    src/simulatorConfig_tests.cpp
    src/systemConfig_tests.cpp
    src/simulatorTask_tests.cpp
    )

add_compile_definitions(
    TEST_DATA_DIR="${PROJECT_SOURCE_DIR}/data")

add_executable(my_tests ${SOURCE_FILES})
target_link_libraries(my_tests 
    common config logging 
    task gtest gmock nlohmann_json::nlohmann_json)
install(TARGETS my_tests DESTINATION bin)

