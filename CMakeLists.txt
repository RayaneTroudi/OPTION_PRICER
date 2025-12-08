cmake_minimum_required(VERSION 3.10)

project(OptionPricer LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include_directories(include)


file(GLOB_RECURSE SRC_FILES_IN_SUBDIRS "src/*.cpp")


set(SOURCE_FILES 
    main.cpp 
    ${SRC_FILES_IN_SUBDIRS}
)

add_executable(pricer_test ${SOURCE_FILES})