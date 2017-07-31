#pragma once

#define BEZIER_ASSERT(x) if (x); else abort();

#define ASSERT_BINOMIAL_COEFFICIENT(N, pos, val) \
    BEZIER_ASSERT(Bezier::Bezier<N>::binomialCoefficients[pos] == val);

#define ASSERT_POLYNOMIAL_COEFFICIENTS(N, pos, a, b) \
    BEZIER_ASSERT(Bezier::Bezier<N>::polynomialCoefficients[pos].one_minus_t  == a); \
    BEZIER_ASSERT(Bezier::Bezier<N>::polynomialCoefficients[pos].t            == b);

#define FUZZY_EPSILON 0.0001

#define FUZZY_ASSERT(val, correctVal) \
{ \
    BEZIER_ASSERT(val <= correctVal + FUZZY_EPSILON); \
    BEZIER_ASSERT(val >= correctVal - FUZZY_EPSILON); \
}

#define FUZZY_ASSERT_POINT(point, x2, y2) \
{ \
    FUZZY_ASSERT(point.x, x2); \
    FUZZY_ASSERT(point.y, y2); \
}
