#pragma once

#define BEZIER_ASSERT(x) if (x); else abort();

#define ASSERT_BINOMIAL_COEFFICIENT(N, pos, val) \
    BEZIER_ASSERT(Bezier::Bezier<N>::binomialCoefficients[pos] == val);

#define FUZZY_EPSILON 0.0001

#define FUZZY_COMPARE(val, correctVal) \
{ \
    BEZIER_ASSERT(val <= correctVal + FUZZY_EPSILON); \
    BEZIER_ASSERT(val >= correctVal - FUZZY_EPSILON); \
}

#define FUZZY_COMPARE_POINT(point, x2, y2) \
{ \
    FUZZY_COMPARE(point.x, x2); \
    FUZZY_COMPARE(point.y, y2); \
}
