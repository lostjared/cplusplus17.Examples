cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(cmd-switch LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build configuration is: ${CMAKE_BUILD_TYPE}")
message(STATUS "is the C++ compiler loaded? ${CMAKE_CXX_COMPILER_LOADED}")

if(CMAKE_CXX_COMPILER_LOADED)
	message(STATUS "The C++ Compiler ID is: ${CMAKE_CXX_COMPILER_ID}")
	message(STATUS "The C++ Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQURIED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
list(APPEND COMPILER_FLAGS "-Wall" "-pedantic" "-ansi" "-Ofast")
else()
message(STATUS "Debug Mode")
list(APPEND COMPILER_FLAGS "-Wall" "-pedantic" "-ansi")
endif()

list(APPEND source_files 
${CMAKE_SOURCE_DIR}/source/cmd-switch.cpp
)

list(APPEND install_headers ${CMAKE_SOURCE_DIR}/source/cmd-switch.hpp)
add_library(cmd-switch ${source_files})	
add_executable(cmd-switch-test ${CMAKE_SOURCE_DIR}/source/switch-test.cpp)
target_link_libraries(cmd-switch-test cmd-switch)
install(TARGETS cmd-switch  DESTINATION lib)
install(FILES ${install-headers} DESTINATION include/cmd-switch)

