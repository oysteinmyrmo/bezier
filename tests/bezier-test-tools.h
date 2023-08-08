#pragma once
#include <bezier/bezier.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace Bezier
{
namespace Test
{
template<size_t N>
void checkPolynomialCoefficients(const size_t idx, const size_t one_minus_t, const size_t t)
{
    INFO("Failure: checkPolynomialCoefficients<" << N << ">(" << idx << ", " << one_minus_t << ", " << t << ");");
    CHECK(::Bezier::Bezier<N>::polynomialCoefficients[idx].one_minus_t == one_minus_t);
    CHECK(::Bezier::Bezier<N>::polynomialCoefficients[idx].t == t);
}

void fuzzyCheckPoint(const ::Bezier::Point p, const double x, const double y, const double epsilon = 1.0e-4);
} // namespace Test
} // namespace Bezier
