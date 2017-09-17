set(TEST_NAME address-recognition-test)

set(CATCH_DIR D:/skola/Catch/single_include)
add_library(Catch INTERFACE)

include_directories(Catch INTERFACE ${CATCH_DIR})
include_directories("../include")

file(GLOB TEST_SOURCES *.cpp)

add_executable(${TEST_NAME} ${TEST_SOURCES})
target_include_directories(Catch INTERFACE ${CATCH_DIR})
target_link_libraries(${TEST_NAME} Catch ${PROJECT_LIB})