include(FetchContent)

FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(catch2)

add_executable(bezier-tests
    bezier-test-tools.cpp
    bezier-test-tools.h
    test_beziers.cpp
    test_beziers.h
    basic-tests.cpp
    derivative-tests.cpp
)

target_link_libraries(bezier-tests PRIVATE Catch2::Catch2WithMain bezier)

add_test(NAME bezier-tests COMMAND bezier-tests --durations yes)
