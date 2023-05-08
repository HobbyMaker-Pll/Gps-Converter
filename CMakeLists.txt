cmake_minimum_required(VERSION 3.0.0)
project(GpsConverter VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source SOURCES)

add_executable(GpsConverter ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${SOURCES})
include(CPack)
