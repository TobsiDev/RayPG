add_library(testLib
            test.h
            test.cpp
            )

target_include_directories(testLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")