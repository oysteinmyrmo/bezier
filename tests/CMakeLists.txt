include_directories(${SIMPLE_BEZIER_INCLUDE_DIR})
set(SB "${SIMPLE_BEZIER_INCLUDE_DIR}/simple_bezier.h")

add_executable(basic-tests basic-tests.cpp ${SB})

add_test(NAME basic-tests COMMAND basic-tests)

