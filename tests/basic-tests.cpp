/*
 * Copyright © 2017 Oystein Myrmo
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
#include "bezier.h"
#include "assert.h"

void binomial_tests()
{
    BEZIER_ASSERT(Bezier::Bezier<0>::binomialCoefficients.size() == 1);
    BEZIER_ASSERT(Bezier::Bezier<1>::binomialCoefficients.size() == 2);
    BEZIER_ASSERT(Bezier::Bezier<2>::binomialCoefficients.size() == 3);
    BEZIER_ASSERT(Bezier::Bezier<3>::binomialCoefficients.size() == 4);
    BEZIER_ASSERT(Bezier::Bezier<4>::binomialCoefficients.size() == 5);
    BEZIER_ASSERT(Bezier::Bezier<5>::binomialCoefficients.size() == 6);
    BEZIER_ASSERT(Bezier::Bezier<10>::binomialCoefficients.size() == 11);
    BEZIER_ASSERT(Bezier::Bezier<15>::binomialCoefficients.size() == 16);
    BEZIER_ASSERT(Bezier::Bezier<20>::binomialCoefficients.size() == 21);
    BEZIER_ASSERT(Bezier::Bezier<50>::binomialCoefficients.size() == 51);

    // N = 0 --> [1]
    ASSERT_BINOMIAL_COEFFICIENT(0, 0, 1);

    // N = 1 --> [1 1]
    ASSERT_BINOMIAL_COEFFICIENT(1, 0, 1);
    ASSERT_BINOMIAL_COEFFICIENT(1, 1, 1);

    // N = 2 --> [1 2 1]
    ASSERT_BINOMIAL_COEFFICIENT(2, 0, 1);
    ASSERT_BINOMIAL_COEFFICIENT(2, 1, 2);
    ASSERT_BINOMIAL_COEFFICIENT(2, 2, 1);

    // N = 3 --> [1 3 3 1]
    ASSERT_BINOMIAL_COEFFICIENT(3, 0, 1);
    ASSERT_BINOMIAL_COEFFICIENT(3, 1, 3);
    ASSERT_BINOMIAL_COEFFICIENT(3, 2, 3);
    ASSERT_BINOMIAL_COEFFICIENT(3, 3, 1);

    // N = 4 --> [1 4 6 4 1]
    ASSERT_BINOMIAL_COEFFICIENT(4, 0, 1);
    ASSERT_BINOMIAL_COEFFICIENT(4, 1, 4);
    ASSERT_BINOMIAL_COEFFICIENT(4, 2, 6);
    ASSERT_BINOMIAL_COEFFICIENT(4, 3, 4);
    ASSERT_BINOMIAL_COEFFICIENT(4, 4, 1);

    // N = 5 --> [1 5 10 10 5 1]
    ASSERT_BINOMIAL_COEFFICIENT(5, 0, 1);
    ASSERT_BINOMIAL_COEFFICIENT(5, 1, 5);
    ASSERT_BINOMIAL_COEFFICIENT(5, 2, 10);
    ASSERT_BINOMIAL_COEFFICIENT(5, 3, 10);
    ASSERT_BINOMIAL_COEFFICIENT(5, 4, 5);
    ASSERT_BINOMIAL_COEFFICIENT(5, 5, 1);

    // N = 10 --> [1 10 45 120 210 252 210 120 45 10 1]
    ASSERT_BINOMIAL_COEFFICIENT(10, 0, 1);
    ASSERT_BINOMIAL_COEFFICIENT(10, 1, 10);
    ASSERT_BINOMIAL_COEFFICIENT(10, 2, 45);
    ASSERT_BINOMIAL_COEFFICIENT(10, 3, 120);
    ASSERT_BINOMIAL_COEFFICIENT(10, 4, 210);
    ASSERT_BINOMIAL_COEFFICIENT(10, 5, 252);
    ASSERT_BINOMIAL_COEFFICIENT(10, 6, 210);
    ASSERT_BINOMIAL_COEFFICIENT(10, 7, 120);
    ASSERT_BINOMIAL_COEFFICIENT(10, 8, 45);
    ASSERT_BINOMIAL_COEFFICIENT(10, 9, 10);
    ASSERT_BINOMIAL_COEFFICIENT(10, 10, 1);

    // N = 10 --> [1 10 45 120 210 252 210 120 45 10 1]
    ASSERT_BINOMIAL_COEFFICIENT(10, 0, 1);
    ASSERT_BINOMIAL_COEFFICIENT(10, 1, 10);
    ASSERT_BINOMIAL_COEFFICIENT(10, 2, 45);
    ASSERT_BINOMIAL_COEFFICIENT(10, 3, 120);
    ASSERT_BINOMIAL_COEFFICIENT(10, 4, 210);
    ASSERT_BINOMIAL_COEFFICIENT(10, 5, 252);
    ASSERT_BINOMIAL_COEFFICIENT(10, 6, 210);
    ASSERT_BINOMIAL_COEFFICIENT(10, 7, 120);
    ASSERT_BINOMIAL_COEFFICIENT(10, 8, 45);
    ASSERT_BINOMIAL_COEFFICIENT(10, 9, 10);
    ASSERT_BINOMIAL_COEFFICIENT(10, 10, 1);
    ASSERT_BINOMIAL_COEFFICIENT(10, 6, 210);
    ASSERT_BINOMIAL_COEFFICIENT(10, 7, 120);
    ASSERT_BINOMIAL_COEFFICIENT(10, 8, 45);
    ASSERT_BINOMIAL_COEFFICIENT(10, 9, 10);
    ASSERT_BINOMIAL_COEFFICIENT(10, 10, 1);

    // N = 15 --> [1 15 105 455 1365 3003 5005 6435 6435 5005 3003 1365 455 105 15 1]
    ASSERT_BINOMIAL_COEFFICIENT(15, 0, 1);
    ASSERT_BINOMIAL_COEFFICIENT(15, 1, 15);
    ASSERT_BINOMIAL_COEFFICIENT(15, 2, 105);
    ASSERT_BINOMIAL_COEFFICIENT(15, 3, 455);
    ASSERT_BINOMIAL_COEFFICIENT(15, 4, 1365);
    ASSERT_BINOMIAL_COEFFICIENT(15, 5, 3003);
    ASSERT_BINOMIAL_COEFFICIENT(15, 6, 5005);
    ASSERT_BINOMIAL_COEFFICIENT(15, 7, 6435);
    ASSERT_BINOMIAL_COEFFICIENT(15, 8, 6435);
    ASSERT_BINOMIAL_COEFFICIENT(15, 9, 5005);
    ASSERT_BINOMIAL_COEFFICIENT(15, 10, 3003);
    ASSERT_BINOMIAL_COEFFICIENT(15, 11, 1365);
    ASSERT_BINOMIAL_COEFFICIENT(15, 12, 455);
    ASSERT_BINOMIAL_COEFFICIENT(15, 13, 105);
    ASSERT_BINOMIAL_COEFFICIENT(15, 14, 15);
    ASSERT_BINOMIAL_COEFFICIENT(15, 15, 1);

    // N = 20 --> [1 20 190 1140 4845 15504 38760 77520 125970 167960 184756 167960 125970 77520 38760 15504 4845 1140 190 20 1]
    ASSERT_BINOMIAL_COEFFICIENT(20, 0, 1);
    ASSERT_BINOMIAL_COEFFICIENT(20, 1, 20);
    ASSERT_BINOMIAL_COEFFICIENT(20, 2, 190);
    ASSERT_BINOMIAL_COEFFICIENT(20, 3, 1140);
    ASSERT_BINOMIAL_COEFFICIENT(20, 4, 4845);
    ASSERT_BINOMIAL_COEFFICIENT(20, 5, 15504);
    ASSERT_BINOMIAL_COEFFICIENT(20, 6, 38760);
    ASSERT_BINOMIAL_COEFFICIENT(20, 7, 77520);
    ASSERT_BINOMIAL_COEFFICIENT(20, 8, 125970);
    ASSERT_BINOMIAL_COEFFICIENT(20, 9, 167960);
    ASSERT_BINOMIAL_COEFFICIENT(20, 10, 184756);
    ASSERT_BINOMIAL_COEFFICIENT(20, 11, 167960);
    ASSERT_BINOMIAL_COEFFICIENT(20, 12, 125970);
    ASSERT_BINOMIAL_COEFFICIENT(20, 13, 77520);
    ASSERT_BINOMIAL_COEFFICIENT(20, 14, 38760);
    ASSERT_BINOMIAL_COEFFICIENT(20, 15, 15504);
    ASSERT_BINOMIAL_COEFFICIENT(20, 16, 4845);
    ASSERT_BINOMIAL_COEFFICIENT(20, 17, 1140);
    ASSERT_BINOMIAL_COEFFICIENT(20, 18, 190);
    ASSERT_BINOMIAL_COEFFICIENT(20, 19, 20);
    ASSERT_BINOMIAL_COEFFICIENT(20, 20, 1);
}

#define ASSERT_POLYNOMIAL_COEFFICIENTS(N, pos, a, b) \
    BEZIER_ASSERT(Bezier::Bezier<N>::polynomialCoefficients[pos].one_minus_t  == a); \
    BEZIER_ASSERT(Bezier::Bezier<N>::polynomialCoefficients[pos].t            == b);

void polynomial_tests()
{
    ASSERT_POLYNOMIAL_COEFFICIENTS(0, 0, 0, 0);

    ASSERT_POLYNOMIAL_COEFFICIENTS(1, 0, 1, 0);
    ASSERT_POLYNOMIAL_COEFFICIENTS(1, 1, 0, 1);

    ASSERT_POLYNOMIAL_COEFFICIENTS(2, 0, 2, 0);
    ASSERT_POLYNOMIAL_COEFFICIENTS(2, 1, 1, 1);
    ASSERT_POLYNOMIAL_COEFFICIENTS(2, 2, 0, 2);

    ASSERT_POLYNOMIAL_COEFFICIENTS(3, 0, 3, 0);
    ASSERT_POLYNOMIAL_COEFFICIENTS(3, 1, 2, 1);
    ASSERT_POLYNOMIAL_COEFFICIENTS(3, 2, 1, 2);
    ASSERT_POLYNOMIAL_COEFFICIENTS(3, 3, 0, 3);

    ASSERT_POLYNOMIAL_COEFFICIENTS(4, 0, 4, 0);
    ASSERT_POLYNOMIAL_COEFFICIENTS(4, 1, 3, 1);
    ASSERT_POLYNOMIAL_COEFFICIENTS(4, 2, 2, 2);
    ASSERT_POLYNOMIAL_COEFFICIENTS(4, 3, 1, 3);
    ASSERT_POLYNOMIAL_COEFFICIENTS(4, 4, 0, 4);

    ASSERT_POLYNOMIAL_COEFFICIENTS(5, 0, 5, 0);
    ASSERT_POLYNOMIAL_COEFFICIENTS(5, 1, 4, 1);
    ASSERT_POLYNOMIAL_COEFFICIENTS(5, 2, 3, 2);
    ASSERT_POLYNOMIAL_COEFFICIENTS(5, 3, 2, 3);
    ASSERT_POLYNOMIAL_COEFFICIENTS(5, 4, 1, 4);
    ASSERT_POLYNOMIAL_COEFFICIENTS(5, 5, 0, 5);

    ASSERT_POLYNOMIAL_COEFFICIENTS(10, 0, 10, 0);
    ASSERT_POLYNOMIAL_COEFFICIENTS(10, 1, 9, 1);
    ASSERT_POLYNOMIAL_COEFFICIENTS(10, 2, 8, 2);
    ASSERT_POLYNOMIAL_COEFFICIENTS(10, 3, 7, 3);
    ASSERT_POLYNOMIAL_COEFFICIENTS(10, 4, 6, 4);
    ASSERT_POLYNOMIAL_COEFFICIENTS(10, 5, 5, 5);
    ASSERT_POLYNOMIAL_COEFFICIENTS(10, 6, 4, 6);
    ASSERT_POLYNOMIAL_COEFFICIENTS(10, 7, 3, 7);
    ASSERT_POLYNOMIAL_COEFFICIENTS(10, 8, 2, 8);
    ASSERT_POLYNOMIAL_COEFFICIENTS(10, 9, 1, 9);
    ASSERT_POLYNOMIAL_COEFFICIENTS(10, 10, 0, 10);
}

void control_points_tests()
{
    Bezier::Bezier<2> bezier2;
    assert(bezier2.size() == 3);

    Bezier::Point &p = bezier2[0];
    assert(p.x == 0.0f);
    assert(p.y == 0.0f);

    p.set(1.0f, 2.0f);
    assert(bezier2[0].x == 1.0f);
    assert(bezier2[0].y == 2.0f);

    p.move(1, -1);
    assert(bezier2[0].x == 2.0f);
    assert(bezier2[0].y == 1.0f);
}

void values_tests()
{
    std::vector<Bezier::Point> cp(4);
    cp[0].set(120, 160);
    cp[1].set(35, 200);
    cp[2].set(220, 260);
    cp[3].set(220, 40);
    Bezier::Bezier<3> bz(cp);

    Bezier::Point val = bz.valueAt(0);
    FUZZY_COMPARE_POINT(val, 120, 160);

    val = bz.valueAt(1);
    FUZZY_COMPARE_POINT(val, 220, 40);

    val = bz.valueAt(0.25);
    FUZZY_COMPARE_POINT(val, 99.765625, 189.0625);

    val = bz.valueAt(0.50);
    FUZZY_COMPARE_POINT(val, 138.125, 197.5);

    val = bz.valueAt(0.75);
    FUZZY_COMPARE_POINT(val, 192.421875, 157.1875);

    val = bz.valueAt(-0.35);
    FUZZY_COMPARE_POINT(val, 327.983124, 138.212509);

    val = bz.valueAt(1.5);
    FUZZY_COMPARE_POINT(val, 24.375, -537.5);

    std::vector<Bezier::Point> cp2(3);
    cp2[0].set(70, 155);
    cp2[1].set(20, 110);
    cp2[2].set(100, 75);
    Bezier::Bezier<2> bz2(cp2);

    val = bz2.valueAt(0);
    FUZZY_COMPARE_POINT(val, 70, 155);

    val = bz2.valueAt(1);
    FUZZY_COMPARE_POINT(val, 100, 75);

    val = bz2.valueAt(0.5);
    FUZZY_COMPARE_POINT(val, 52.5, 112.5);

    val = bz2.valueAt(-1.0);
    FUZZY_COMPARE_POINT(val, 300, 255);

    val = bz2.valueAt(2.0);
    FUZZY_COMPARE_POINT(val, 390, 15);
}

void derivatives_tests()
{
    std::vector<Bezier::Point> controlPoints3(4);
    controlPoints3[0] = Bezier::Point(120, 160);
    controlPoints3[1] = Bezier::Point(35, 200);
    controlPoints3[2] = Bezier::Point(220, 260);
    controlPoints3[3] = Bezier::Point(220, 40);

    Bezier::Bezier<3> bezier3(controlPoints3);
    Bezier::Bezier<2> bezier2 = bezier3.derivative();
    Bezier::Bezier<1> bezier1 = bezier2.derivative();
    Bezier::Bezier<0> bezier0 = bezier1.derivative();

    assert(bezier3.size() == 4);
    assert(bezier2.size() == 3);
    assert(bezier1.size() == 2);
    assert(bezier0.size() == 1);
}

int main()
{
    binomial_tests();
    polynomial_tests();
    control_points_tests();
    values_tests();
    derivatives_tests();
    return 0;
}

