project(ShadowContainerTests)

set(TEST_FILES test.cpp)

add_executable(ShadowTests ${TEST_FILES})
target_compile_features(ShadowTests PRIVATE cxx_std_23)