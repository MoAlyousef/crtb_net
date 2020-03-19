cmake_minimum_required(VERSION 3.0)
project(crtb_net VERSION 0.0.1)

option(CRTB_ENABLE_SSL "Finds and links OpenSSL" OFF)
option(CRTB_BUILD_EXAMPLES "Builds examples" OFF)

find_package(Threads REQUIRED)

if(CRTB_ENABLE_SSL)
    find_package(OpenSSL REQUIRED)
endif()

include_directories(include .ext/rtb/include)

add_library(crtb_net STATIC src/crtb_net.cpp)

set_target_properties(crtb_net PROPERTIES CXX_STANDARD 17)

if(CRTB_ENABLE_SSL)
    target_compile_definitions(crtb_net PUBLIC RTB_ENABLE_SSL)
    target_link_libraries(crtb_net PUBLIC Threads::Threads OpenSSL::Crypto OpenSSL::SSL)
else()
    target_link_libraries(crtb_net PUBLIC Threads::Threads)
endif()

if(WIN32)
    target_compile_definitions(crtb_net PUBLIC WIN32_LEAN_AND_MEAN)
    target_link_libraries(crtb_net PUBLIC wsock32 ws2_32)
endif()

target_include_directories(
    crtb_net
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/crtb_netConfigVersion.cmake" 
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(TARGETS crtb_net
    EXPORT crtb_netTargets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/crtb_netConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/crtb_netConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/crtb_net
)

install(EXPORT crtb_netTargets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/crtb_net)
install(FILES "${PROJECT_BINARY_DIR}/crtb_netConfig.cmake" "${PROJECT_BINARY_DIR}/crtb_netConfigVersion.cmake" DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/crtb_net)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include" DESTINATION .)

if(CRTB_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
