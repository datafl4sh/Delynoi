cmake_minimum_required(VERSION 3.30)
project(Delynoi)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address")

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

# Targets that we develop here
enable_testing()
add_subdirectory(lib/utilities)
add_subdirectory(delynoi)
add_subdirectory(test)
