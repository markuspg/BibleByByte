cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project(StorageCacheTest
        LANGUAGES CXX)

find_package(Qt5Test REQUIRED)

add_executable(${PROJECT_NAME}
    storagecachetest.cpp
    ../../src/storagecache.cpp
    ../../src/modules/helpers.cpp)
target_compile_definitions(${PROJECT_NAME} PRIVATE CACHE_TEST)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ../../src)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Test)

add_test(NAME StorageCacheTester COMMAND ${PROJECT_NAME})
