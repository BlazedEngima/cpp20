set(MODULE_NAME cache)
set(TEST_NAME test_${MODULE_NAME})

add_executable(${TEST_NAME} test/test.cpp)

target_include_directories(${TEST_NAME} PUBLIC include/)
target_link_libraries(${TEST_NAME} GTest::gtest_main)
target_compile_options(${TEST_NAME} PUBLIC "${WARNING_FLAGS} -fexceptions")

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
