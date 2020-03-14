cmake_minimum_required(VERSION 3.0)
project(crtb_net_examples)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS /std:c++17)
else()
    set(CMAKE_CXX_FLAGS -std=c++17)
    set(CMAKE_C_FLAGS -std=c89)
endif()

option(RTB_ENABLE_SSL "Finds and links OpenSSL" OFF)
option(RTB_BUILD_EXAMPLES "Builds examples" OFF)

find_package(Threads REQUIRED)

if(RTB_ENABLE_SSL)
    find_package(OpenSSL REQUIRED)
endif()

include_directories(include .ext/rtb/include)

add_library(crtb_net STATIC libsrc/crtb_net.cpp)

if(RTB_ENABLE_SSL)
    target_compile_definitions(crtb_net PUBLIC rtb_ENABLE_SSL)
    target_link_libraries(crtb_net PUBLIC Threads::Threads OpenSSL::Crypto OpenSSL::SSL)
else()
    target_link_libraries(crtb_net PUBLIC Threads::Threads)
endif()

if(WIN32)
    target_compile_definitions(crtb_net PUBLIC WIN32_LEAN_AND_MEAN)
    target_link_libraries(crtb_net PUBLIC wsock32 ws2_32)
endif()

add_executable(main src/main.c)
target_link_libraries(main PRIVATE crtb_net)

if(RTB_BUILD_EXAMPLES)
    add_executable(server examples/server.c)
    add_executable(client examples/client.c)
    add_executable(async_client examples/async_client.c)
    target_link_libraries(server PRIVATE crtb_net)
    target_link_libraries(client PRIVATE crtb_net)
    target_link_libraries(async_client PRIVATE crtb_net)
    if(RTB_ENABLE_SSL)
        add_executable(ssl_client examples/ssl_client.c)
        target_link_libraries(ssl_client PRIVATE crtb_net)
    endif()
endif()
