add_library(src 
            #entity.h
            #entity.cpp
            window.h
            window.cpp
            )

#add_subdirectory(subfolder)
#target_link_libraries(testLib)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/subfolder)
target_include_directories(src PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
