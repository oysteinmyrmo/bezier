include_directories(${BEZIER_INCLUDE_DIR})
set(BEZIER "${BEZIER_INCLUDE_DIR}/bezier.h")

add_executable(basic-tests basic-tests.cpp assert.h ${BEZIER})

add_test(NAME basic-tests COMMAND basic-tests)

