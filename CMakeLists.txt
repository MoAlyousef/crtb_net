cmake_minimum_required(VERSION 3.0)
project(crtb_server_example)

# required for gcc
find_package(Threads REQUIRED)

add_library(crtb_net SHARED rtb_server.cpp)
add_executable(server main.c)

# requires that the rtb repo (from github.com/moalyousef/rtb) be cloned into the parent dir
target_include_directories(crtb_net PUBLIC ${CMAKE_PROJECT_DIRECTORY}../rtb/include)

target_compile_options(crtb_net PUBLIC -std=c++17)
if(WIN32)
target_compile_definitions(crtb_net PUBLIC WIN32_LEAN_AND_MEAN)
target_link_libraries(crtb_net PUBLIC wsock32 ws2_32)
endif()
target_link_libraries(crtb_net PUBLIC Threads::Threads)

target_link_libraries(server PRIVATE crtb_net)
