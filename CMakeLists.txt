cmake_minimum_required(VERSION 3.16)
project(MyGeometry VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)

file(GLOB_RECURSE MYHEADERS ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE MYSOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM MYSOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp)

foreach (header IN LISTS MYHEADERS)
    message(${header})
endforeach ()

add_library(MyGeometry SHARED ${MYHEADERS} ${MYSOURCES} )
target_link_libraries(MyGeometry PUBLIC Eigen3::Eigen)
#target_include_directories(MyGeometry PUBLIC )

add_executable(test ${MYHEADERS} ${MYSOURCES} ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(test PUBLIC Eigen3::Eigen)

message("CMAKE_INSTALL_PREFIX: " ${CMAKE_INSTALL_PREFIX})
message("CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR})
include(GNUInstallDirs)
message("CMAKE_INSTALL_INCLUDEDIR: " ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS MyGeometry
        EXPORT MyGeometryTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        TYPE INCLUDE
        FILES_MATCHING PATTERN "*.h")

install(EXPORT MyGeometryTargets
        FILE MyGeometryTargets.cmake
        DESTINATION lib/cmake/MyGeometry)

include(CMakePackageConfigHelpers)
#configure_package_config_file(
#        MyGeometryConfig.cmake.in
#        MyGeometryConfig.cmake
#        INSTALL_DESTINATION lib/cmake/test_message)
#
#
write_basic_package_version_file(
        "MyGeometryConfigVersion.cmake"
        VERSION ${MyGeometry_VERSION}
        COMPATIBILITY AnyNewerVersion)

install(FILES "MyGeometryConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/MyGeometryConfigVersion.cmake"
        DESTINATION lib/cmake/MyGeometry)
