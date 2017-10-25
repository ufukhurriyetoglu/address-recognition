cmake_minimum_required(VERSION 3.6)
set(PROJECT_NAME address-recognition)
set(PROJECT_LIB address-recognition-lib)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-o3")
set(BOOST_ROOT "D:/skola/boost_1_64_0")

find_package(Boost REQUIRED iostreams system chrono)

include_directories("include")

file(GLOB SOURCES src/*.cpp include/*.hpp)
list(REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_library(${PROJECT_LIB} STATIC ${SOURCES})

enable_testing()
add_subdirectory(test)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIB})

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found, unable to continue.")
else ()
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif ()
