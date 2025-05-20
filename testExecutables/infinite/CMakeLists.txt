cmake_minimum_required(VERSION 3.16)
project(infinite)

set(SOURCE_FILES 
    main.cpp 
    )

add_executable(infinite ${SOURCE_FILES})
target_link_libraries(infinite)
install(TARGETS infinite DESTINATION bin)
