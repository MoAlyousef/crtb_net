cmake_minimum_required(VERSION 3.0)
project(crtb_net_examples)

# required for gcc
find_package(Threads REQUIRED)

add_library(crtb_net SHARED src/crtb_net.cpp)
add_executable(server examples/server_example.c)
add_executable(client examples/client_example.c)
add_executable(async_client examples/async_client_example.c)

target_include_directories(crtb_net PUBLIC include ext/rtb/include)
target_include_directories(server PUBLIC include)
target_include_directories(client PUBLIC include)
target_include_directories(async_client PUBLIC include)

target_compile_options(crtb_net PUBLIC -std=c++17)
target_compile_options(server PUBLIC -std=c89)
target_compile_options(client PUBLIC -std=c89)
target_compile_options(async_client PUBLIC -std=c89)

if(WIN32)
target_compile_definitions(crtb_net PUBLIC WIN32_LEAN_AND_MEAN)
target_link_libraries(crtb_net PUBLIC wsock32 ws2_32)
endif()

target_link_libraries(crtb_net PUBLIC Threads::Threads)
target_link_libraries(server PRIVATE crtb_net)
target_link_libraries(client PRIVATE crtb_net)
target_link_libraries(async_client PRIVATE crtb_net)
