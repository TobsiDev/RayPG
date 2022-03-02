cmake_minimum_required(VERSION 3.0.0)
project(RaylibRPG VERSION 0.1.0)

# ###
# # Dependencies
# find_package(raylib 4.0.0 QUIET) # QUIET or REQUIRED
# if (NOT raylib_FOUND) # If there's none, fetch and build raylib
#   include(FetchContent)
#   FetchContent_Declare(
#     raylib
#     URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
#   )
#   FetchContent_GetProperties(raylib)
#   if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
#     set(FETCHCONTENT_QUIET NO)
#     FetchContent_Populate(raylib)
#     set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
#     add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
#   endif()
# endif()
# #
# ###

include(CTest)
enable_testing()

add_subdirectory(src) # Adds a subfolder here

# If you have to include lib's via vcpkg
# you can add them here

add_executable(RayPG main.cpp)
target_link_libraries(RayPG PRIVATE src raylib) #testLib is the name I gave the temp subfolder

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)