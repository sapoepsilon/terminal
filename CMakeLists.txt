cmake_minimum_required(VERSION 3.21)
project(terminal)

set(CMAKE_CXX_STANDARD 17)

# Add the Cocoa framework
find_library(COCOA_LIBRARY Cocoa)
if (NOT COCOA_LIBRARY)
    message(FATAL_ERROR "Cocoa framework not found.")
endif()

# Add your source files
set(SOURCES
        main.cpp
        )

add_executable(terminal ${SOURCES})

# Link the Cocoa framework
target_link_libraries(terminal PRIVATE ${COCOA_LIBRARY})
