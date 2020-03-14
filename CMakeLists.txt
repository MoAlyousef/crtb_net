cmake_minimum_required(VERSION 3.0)
project(crtb_net_examples)

if(${CMAKE_CXX_COMPILER_ID} MATCHES "MSVC")
set(CMAKE_CXX_FLAGS /std:c++17)
else()
set(CMAKE_CXX_FLAGS -std=c++17)
set(CMAKE_C_FLAGS -std=c89)
endif()

option(RTB_ENABLE_SSL "Finds and links OpenSSL" OFF)

# required for gcc
find_package(Threads REQUIRED)

if(RTB_ENABLE_SSL)
    find_package(OpenSSL REQUIRED)
endif()

add_library(crtb_net SHARED src/crtb_net.cpp)
add_executable(server examples/server.c)
add_executable(client examples/client.c)
add_executable(async_client examples/async_client.c)

if(RTB_ENABLE_SSL)
    add_executable(ssl_client examples/ssl_client.c)
endif()

target_include_directories(crtb_net PUBLIC include ext/rtb/include)
target_include_directories(server PUBLIC include)
target_include_directories(client PUBLIC include)
target_include_directories(async_client PUBLIC include)

if(RTB_ENABLE_SSL)
    target_include_directories(ssl_client PUBLIC include)
endif()

if(WIN32)
target_compile_definitions(crtb_net PUBLIC WIN32_LEAN_AND_MEAN)
target_link_libraries(crtb_net PUBLIC wsock32 ws2_32)
endif()

if(RTB_ENABLE_SSL)
    target_compile_definitions(crtb_net PUBLIC rtb_ENABLE_SSL)
    target_link_libraries(crtb_net PUBLIC Threads::Threads OpenSSL::Crypto OpenSSL::SSL)
else()
    target_link_libraries(crtb_net PUBLIC Threads::Threads)
endif()

target_link_libraries(server PRIVATE crtb_net)
target_link_libraries(client PRIVATE crtb_net)
target_link_libraries(async_client PRIVATE crtb_net)

if(RTB_ENABLE_SSL)
    target_link_libraries(ssl_client PRIVATE crtb_net)
endif()
