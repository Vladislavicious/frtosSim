cmake_minimum_required(VERSION 3.16)

project(dipl_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS 
  "${CMAKE_CXX_FLAGS} -std=c++20 -O1")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(DIVISIBLE_INSTALL_INCLUDE_DIR 
  ${PROJECT_SOURCE_DIR}/include)
set(DIVISIBLE_INSTALL_BIN_DIR 
  ${PROJECT_SOURCE_DIR}/bin)
set(DIVISIBLE_INSTALL_LIB_DIR 
  ${PROJECT_SOURCE_DIR}/lib)

include_directories(${DIVISIBLE_INSTALL_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(testExecutables)
