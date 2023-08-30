/*
 * Copyright © 2023 Oystein Myrmo
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include <bezier/bezier.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test compile time binomial coefficients", "[binomial_coefficients][compile_time]")
{
    static_assert(bezier::BinomialCoefficients<0>::size() == 1, "");
    static_assert(bezier::BinomialCoefficients<0>::size() == 1, "");
    static_assert(bezier::BinomialCoefficients<1>::size() == 2, "");
    static_assert(bezier::BinomialCoefficients<2>::size() == 3, "");
    static_assert(bezier::BinomialCoefficients<3>::size() == 4, "");
    static_assert(bezier::BinomialCoefficients<4>::size() == 5, "");
    static_assert(bezier::BinomialCoefficients<5>::size() == 6, "");
    static_assert(bezier::BinomialCoefficients<10>::size() == 11, "");
    static_assert(bezier::BinomialCoefficients<15>::size() == 16, "");
    static_assert(bezier::BinomialCoefficients<20>::size() == 21, "");
    static_assert(bezier::BinomialCoefficients<50>::size() == 51, "");
}
