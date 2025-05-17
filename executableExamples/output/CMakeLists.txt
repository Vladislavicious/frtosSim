cmake_minimum_required(VERSION 3.16)
project(output)

set(SOURCE_FILES 
    main.cpp 
    )

add_executable(output ${SOURCE_FILES})
target_link_libraries(output)
install(TARGETS output DESTINATION bin)

