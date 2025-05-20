cmake_minimum_required(VERSION 3.16)
project(halfSecond)

set(SOURCE_FILES 
    main.cpp 
    )

add_executable(halfSecond ${SOURCE_FILES})
target_link_libraries(halfSecond)
install(TARGETS halfSecond DESTINATION bin)

