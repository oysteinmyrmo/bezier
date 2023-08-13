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

#include "bezier-test-tools.h"
#include "test_beziers.h"

TEST_CASE("Test binomial coefficients", "[binomial_coefficients]")
{
    CHECK(bezier::Bezier<0>::binomialCoefficients.size() == 1);
    CHECK(bezier::Bezier<1>::binomialCoefficients.size() == 2);
    CHECK(bezier::Bezier<2>::binomialCoefficients.size() == 3);
    CHECK(bezier::Bezier<3>::binomialCoefficients.size() == 4);
    CHECK(bezier::Bezier<4>::binomialCoefficients.size() == 5);
    CHECK(bezier::Bezier<5>::binomialCoefficients.size() == 6);
    CHECK(bezier::Bezier<10>::binomialCoefficients.size() == 11);
    CHECK(bezier::Bezier<15>::binomialCoefficients.size() == 16);
    CHECK(bezier::Bezier<20>::binomialCoefficients.size() == 21);
    CHECK(bezier::Bezier<50>::binomialCoefficients.size() == 51);

    // N = 0 --> [1]
    CHECK(bezier::Bezier<0>::binomialCoefficients[0] == 1);

    // N = 1 --> [1 1]
    CHECK(bezier::Bezier<1>::binomialCoefficients[0] == 1);
    CHECK(bezier::Bezier<1>::binomialCoefficients[1] == 1);

    // N = 2 --> [1 2 1]
    CHECK(bezier::Bezier<2>::binomialCoefficients[0] == 1);
    CHECK(bezier::Bezier<2>::binomialCoefficients[1] == 2);
    CHECK(bezier::Bezier<2>::binomialCoefficients[2] == 1);

    // N = 3 --> [1 3 3 1]
    CHECK(bezier::Bezier<3>::binomialCoefficients[0] == 1);
    CHECK(bezier::Bezier<3>::binomialCoefficients[1] == 3);
    CHECK(bezier::Bezier<3>::binomialCoefficients[2] == 3);
    CHECK(bezier::Bezier<3>::binomialCoefficients[3] == 1);

    // N = 4 --> [1 4 6 4 1]
    CHECK(bezier::Bezier<4>::binomialCoefficients[0] == 1);
    CHECK(bezier::Bezier<4>::binomialCoefficients[1] == 4);
    CHECK(bezier::Bezier<4>::binomialCoefficients[2] == 6);
    CHECK(bezier::Bezier<4>::binomialCoefficients[3] == 4);
    CHECK(bezier::Bezier<4>::binomialCoefficients[4] == 1);

    // N = 5 --> [1 5 10 10 5 1]
    CHECK(bezier::Bezier<5>::binomialCoefficients[0] == 1);
    CHECK(bezier::Bezier<5>::binomialCoefficients[1] == 5);
    CHECK(bezier::Bezier<5>::binomialCoefficients[2] == 10);
    CHECK(bezier::Bezier<5>::binomialCoefficients[3] == 10);
    CHECK(bezier::Bezier<5>::binomialCoefficients[4] == 5);
    CHECK(bezier::Bezier<5>::binomialCoefficients[5] == 1);

    // N = 10 --> [1 10 45 120 210 252 210 120 45 10 1]
    CHECK(bezier::Bezier<10>::binomialCoefficients[0] == 1);
    CHECK(bezier::Bezier<10>::binomialCoefficients[1] == 10);
    CHECK(bezier::Bezier<10>::binomialCoefficients[2] == 45);
    CHECK(bezier::Bezier<10>::binomialCoefficients[3] == 120);
    CHECK(bezier::Bezier<10>::binomialCoefficients[4] == 210);
    CHECK(bezier::Bezier<10>::binomialCoefficients[5] == 252);
    CHECK(bezier::Bezier<10>::binomialCoefficients[6] == 210);
    CHECK(bezier::Bezier<10>::binomialCoefficients[7] == 120);
    CHECK(bezier::Bezier<10>::binomialCoefficients[8] == 45);
    CHECK(bezier::Bezier<10>::binomialCoefficients[9] == 10);
    CHECK(bezier::Bezier<10>::binomialCoefficients[10] == 1);

    // N = 15 --> [1 15 105 455 1365 3003 5005 6435 6435 5005 3003 1365 455 105 15 1]
    CHECK(bezier::Bezier<15>::binomialCoefficients[0] == 1);
    CHECK(bezier::Bezier<15>::binomialCoefficients[1] == 15);
    CHECK(bezier::Bezier<15>::binomialCoefficients[2] == 105);
    CHECK(bezier::Bezier<15>::binomialCoefficients[3] == 455);
    CHECK(bezier::Bezier<15>::binomialCoefficients[4] == 1365);
    CHECK(bezier::Bezier<15>::binomialCoefficients[5] == 3003);
    CHECK(bezier::Bezier<15>::binomialCoefficients[6] == 5005);
    CHECK(bezier::Bezier<15>::binomialCoefficients[7] == 6435);
    CHECK(bezier::Bezier<15>::binomialCoefficients[8] == 6435);
    CHECK(bezier::Bezier<15>::binomialCoefficients[9] == 5005);
    CHECK(bezier::Bezier<15>::binomialCoefficients[10] == 3003);
    CHECK(bezier::Bezier<15>::binomialCoefficients[11] == 1365);
    CHECK(bezier::Bezier<15>::binomialCoefficients[12] == 455);
    CHECK(bezier::Bezier<15>::binomialCoefficients[13] == 105);
    CHECK(bezier::Bezier<15>::binomialCoefficients[14] == 15);
    CHECK(bezier::Bezier<15>::binomialCoefficients[15] == 1);

    // N = 20 --> [1 20 190 1140 4845 15504 38760 77520 125970 167960 184756 167960 125970 77520 38760 15504 4845 1140 190 20 1]
    CHECK(bezier::Bezier<20>::binomialCoefficients[0] == 1);
    CHECK(bezier::Bezier<20>::binomialCoefficients[1] == 20);
    CHECK(bezier::Bezier<20>::binomialCoefficients[2] == 190);
    CHECK(bezier::Bezier<20>::binomialCoefficients[3] == 1140);
    CHECK(bezier::Bezier<20>::binomialCoefficients[4] == 4845);
    CHECK(bezier::Bezier<20>::binomialCoefficients[5] == 15504);
    CHECK(bezier::Bezier<20>::binomialCoefficients[6] == 38760);
    CHECK(bezier::Bezier<20>::binomialCoefficients[7] == 77520);
    CHECK(bezier::Bezier<20>::binomialCoefficients[8] == 125970);
    CHECK(bezier::Bezier<20>::binomialCoefficients[9] == 167960);
    CHECK(bezier::Bezier<20>::binomialCoefficients[10] == 184756);
    CHECK(bezier::Bezier<20>::binomialCoefficients[11] == 167960);
    CHECK(bezier::Bezier<20>::binomialCoefficients[12] == 125970);
    CHECK(bezier::Bezier<20>::binomialCoefficients[13] == 77520);
    CHECK(bezier::Bezier<20>::binomialCoefficients[14] == 38760);
    CHECK(bezier::Bezier<20>::binomialCoefficients[15] == 15504);
    CHECK(bezier::Bezier<20>::binomialCoefficients[16] == 4845);
    CHECK(bezier::Bezier<20>::binomialCoefficients[17] == 1140);
    CHECK(bezier::Bezier<20>::binomialCoefficients[18] == 190);
    CHECK(bezier::Bezier<20>::binomialCoefficients[19] == 20);
    CHECK(bezier::Bezier<20>::binomialCoefficients[20] == 1);
}

TEST_CASE("Test polynomial coefficients", "[polynomial_coefficients]")
{
    bezier::test::checkPolynomialCoefficients<1>(0, 1, 0);
    bezier::test::checkPolynomialCoefficients<1>(1, 0, 1);

    bezier::test::checkPolynomialCoefficients<2>(0, 2, 0);
    bezier::test::checkPolynomialCoefficients<2>(1, 1, 1);
    bezier::test::checkPolynomialCoefficients<2>(2, 0, 2);

    bezier::test::checkPolynomialCoefficients<3>(0, 3, 0);
    bezier::test::checkPolynomialCoefficients<3>(1, 2, 1);
    bezier::test::checkPolynomialCoefficients<3>(2, 1, 2);
    bezier::test::checkPolynomialCoefficients<3>(3, 0, 3);

    bezier::test::checkPolynomialCoefficients<4>(0, 4, 0);
    bezier::test::checkPolynomialCoefficients<4>(1, 3, 1);
    bezier::test::checkPolynomialCoefficients<4>(2, 2, 2);
    bezier::test::checkPolynomialCoefficients<4>(3, 1, 3);
    bezier::test::checkPolynomialCoefficients<4>(4, 0, 4);

    bezier::test::checkPolynomialCoefficients<5>(0, 5, 0);
    bezier::test::checkPolynomialCoefficients<5>(1, 4, 1);
    bezier::test::checkPolynomialCoefficients<5>(2, 3, 2);
    bezier::test::checkPolynomialCoefficients<5>(3, 2, 3);
    bezier::test::checkPolynomialCoefficients<5>(4, 1, 4);
    bezier::test::checkPolynomialCoefficients<5>(5, 0, 5);

    bezier::test::checkPolynomialCoefficients<10>(0, 10, 0);
    bezier::test::checkPolynomialCoefficients<10>(1, 9, 1);
    bezier::test::checkPolynomialCoefficients<10>(2, 8, 2);
    bezier::test::checkPolynomialCoefficients<10>(3, 7, 3);
    bezier::test::checkPolynomialCoefficients<10>(4, 6, 4);
    bezier::test::checkPolynomialCoefficients<10>(5, 5, 5);
    bezier::test::checkPolynomialCoefficients<10>(6, 4, 6);
    bezier::test::checkPolynomialCoefficients<10>(7, 3, 7);
    bezier::test::checkPolynomialCoefficients<10>(8, 2, 8);
    bezier::test::checkPolynomialCoefficients<10>(9, 1, 9);
    bezier::test::checkPolynomialCoefficients<10>(10, 0, 10);
}

TEST_CASE("Test control points", "[control_points]")
{
    static constexpr double epsilon = 1.0e-9;

    bezier::Bezier<2> bezier2;
    CHECK(bezier2.size() == 3);

    bezier::Point &p = bezier2[0];
    bezier::test::fuzzyCheckPoint(p, 0.0f, 0.0f, epsilon);

    p.set(1.0f, 2.0);
    bezier::test::fuzzyCheckPoint(p, 1.0f, 2.0f, epsilon);

    p.translate(1, -1);
    bezier::test::fuzzyCheckPoint(p, 2.0f, 1.0f, epsilon);
}

TEST_CASE("Test curve locations", "[curves][locations]")
{
    const bezier::Bezier<3> bezier3 = bezier::test::defaultCubicBezier();
    bezier::test::fuzzyCheckPoint(bezier3.valueAt(0.00f), 120.0, 160.0);
    bezier::test::fuzzyCheckPoint(bezier3.valueAt(1.00f), 220.0, 40.0);
    bezier::test::fuzzyCheckPoint(bezier3.valueAt(0.25f), 99.765625, 189.0625);
    bezier::test::fuzzyCheckPoint(bezier3.valueAt(0.50f), 138.125, 197.5);
    bezier::test::fuzzyCheckPoint(bezier3.valueAt(0.75f), 192.421875, 157.1875);
    bezier::test::fuzzyCheckPoint(bezier3.valueAt(-0.35f), 327.983124, 138.212509);
    bezier::test::fuzzyCheckPoint(bezier3.valueAt(1.50f), 24.375, -537.5);

    const bezier::Bezier<2> bezier2 = bezier::test::defaultQuadraticBezier();
    bezier::test::fuzzyCheckPoint(bezier2.valueAt(0.0f), 70.0, 155.0);
    bezier::test::fuzzyCheckPoint(bezier2.valueAt(1.0f), 100.0, 75.0);
    bezier::test::fuzzyCheckPoint(bezier2.valueAt(0.5f), 52.5, 112.5);
    bezier::test::fuzzyCheckPoint(bezier2.valueAt(-1.0f), 300.0, 255.0);
    bezier::test::fuzzyCheckPoint(bezier2.valueAt(2.0f), 390.0, 15.0);
}

TEST_CASE("Test curve lengths", "[curves][lengths]")
{
    static constexpr float epsilon = 1.0e-6f;

    // Using similar curves as https://pomax.github.io/bezierinfo/#arclengthapprox for testing.
    const bezier::Bezier<2> b2({ {  70, 250 }, { 20, 110 }, { 200,  80 } });            // Real length: 256.25
    const bezier::Bezier<3> b3({ { 120, 160 }, { 35, 200 }, { 220, 260 }, {220, 40} }); // Real length: 272.87

    CHECK_THAT(b2.length(0),    Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(b2.length(1),    Catch::Matchers::WithinAbs(214.009338, epsilon));
    CHECK_THAT(b2.length(2),    Catch::Matchers::WithinAbs(248.073410, epsilon));
    CHECK_THAT(b2.length(3),    Catch::Matchers::WithinAbs(252.609528, epsilon));
    CHECK_THAT(b2.length(5),    Catch::Matchers::WithinAbs(254.948517, epsilon));
    CHECK_THAT(b2.length(10),   Catch::Matchers::WithinAbs(255.927200, epsilon));
    CHECK_THAT(b2.length(15),   Catch::Matchers::WithinAbs(256.107788, epsilon));
    CHECK_THAT(b2.length(20),   Catch::Matchers::WithinAbs(256.171021, epsilon));
    CHECK_THAT(b2.length(50),   Catch::Matchers::WithinAbs(256.239044, epsilon));
    CHECK_THAT(b2.length(100),  Catch::Matchers::WithinAbs(256.248718, epsilon));
    CHECK_THAT(b2.length(),     Catch::Matchers::WithinAbs(256.248718, epsilon)); // Same as 100 (default number of intervals)
    CHECK_THAT(b2.length(200),  Catch::Matchers::WithinAbs(256.251160, epsilon));
    CHECK_THAT(b2.length(500),  Catch::Matchers::WithinAbs(256.249878, epsilon));
    CHECK_THAT(b2.length(1000), Catch::Matchers::WithinAbs(256.248779, epsilon));

    CHECK_THAT(b3.length(0),    Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(b3.length(1),    Catch::Matchers::WithinAbs(156.204987, epsilon));
    CHECK_THAT(b3.length(2),    Catch::Matchers::WithinAbs(219.160416, epsilon));
    CHECK_THAT(b3.length(3),    Catch::Matchers::WithinAbs(251.716125, epsilon));
    CHECK_THAT(b3.length(5),    Catch::Matchers::WithinAbs(266.579285, epsilon));
    CHECK_THAT(b3.length(10),   Catch::Matchers::WithinAbs(271.217773, epsilon));
    CHECK_THAT(b3.length(15),   Catch::Matchers::WithinAbs(272.134460, epsilon));
    CHECK_THAT(b3.length(20),   Catch::Matchers::WithinAbs(272.456390, epsilon));
    CHECK_THAT(b3.length(50),   Catch::Matchers::WithinAbs(272.803558, epsilon));
    CHECK_THAT(b3.length(100),  Catch::Matchers::WithinAbs(272.853027, epsilon));
    CHECK_THAT(b3.length(),     Catch::Matchers::WithinAbs(272.853027, epsilon)); // Same as 100 (default number of intervals)
    CHECK_THAT(b3.length(200),  Catch::Matchers::WithinAbs(272.865356, epsilon));
    CHECK_THAT(b3.length(500),  Catch::Matchers::WithinAbs(272.865540, epsilon));
    CHECK_THAT(b3.length(1000), Catch::Matchers::WithinAbs(272.863708, epsilon));
}

TEST_CASE("Test splitting of curves", "[curves][splitting]")
{
    const bezier::Bezier<3> b3({ { 120, 160 }, { 35, 200 }, { 220, 260 }, {220, 40} });
    CHECK(b3.order() == 3);

    const auto split_05 = b3.split();
    bezier::test::fuzzyCheckPoint(split_05.left[0], 120.0, 160.0);
    bezier::test::fuzzyCheckPoint(split_05.left[1], 77.5, 180.0);
    bezier::test::fuzzyCheckPoint(split_05.left[2], 102.5, 205.0);
    bezier::test::fuzzyCheckPoint(split_05.left[3], 138.125, 197.5);
    bezier::test::fuzzyCheckPoint(split_05.right[0], 220.0, 40.0);
    bezier::test::fuzzyCheckPoint(split_05.right[1], 220.0, 150.0);
    bezier::test::fuzzyCheckPoint(split_05.right[2], 173.75, 190.0);
    bezier::test::fuzzyCheckPoint(split_05.right[3], 138.125, 197.5);
    CHECK(split_05.left.order() == b3.order());
    CHECK(split_05.right.order() == b3.order());

    const auto split_08 = b3.split(0.8f);
    bezier::test::fuzzyCheckPoint(split_08.left[0], 120.0, 160.0);
    bezier::test::fuzzyCheckPoint(split_08.left[1], 52.0, 192.0);
    bezier::test::fuzzyCheckPoint(split_08.left[2], 156.8, 236.8);
    bezier::test::fuzzyCheckPoint(split_08.left[3], 201.44, 140.8);
    bezier::test::fuzzyCheckPoint(split_08.right[0], 220.0, 40.0);
    bezier::test::fuzzyCheckPoint(split_08.right[1], 220.0, 84.0);
    bezier::test::fuzzyCheckPoint(split_08.right[2], 212.6, 116.8);
    bezier::test::fuzzyCheckPoint(split_08.right[3], 201.44, 140.8);
    CHECK(split_08.left.order() == b3.order());
    CHECK(split_08.right.order() == b3.order());

    const auto split_033 = b3.split(0.33f);
    bezier::test::fuzzyCheckPoint(split_033.left[0], 120.0, 160.0);
    bezier::test::fuzzyCheckPoint(split_033.left[1], 91.950, 173.2);
    bezier::test::fuzzyCheckPoint(split_033.left[2], 93.303, 188.578);
    bezier::test::fuzzyCheckPoint(split_033.left[3], 107.7077, 195.3529);
    bezier::test::fuzzyCheckPoint(split_033.right[0], 220.0, 40.0);
    bezier::test::fuzzyCheckPoint(split_033.right[1], 220.0, 187.4);
    bezier::test::fuzzyCheckPoint(split_033.right[2], 136.9535, 209.108);
    bezier::test::fuzzyCheckPoint(split_033.right[3], 107.7077, 195.3529);
    CHECK(split_033.left.order() == b3.order());
    CHECK(split_033.right.order() == b3.order());
}

TEST_CASE("Test arch points", "[curves][archs]")
{
    static constexpr float epsilon = 1.0e-4f;

    float t;
    bezier::Point point;

    bezier::Bezier<2> a({ {80, 20}, {50, 10}, {95, 95} });
    t = a.archMidPoint();
    point = a.valueAt(t);
    CHECK_THAT(t, Catch::Matchers::WithinAbs(0.71246, epsilon));
    bezier::test::fuzzyCheckPoint(point, 75.32214, 53.97224);

    bezier::Bezier<2> b({ {70, 250}, {20, 110}, {250, 63} });
    t = b.archMidPoint();
    point = b.valueAt(t);
    CHECK_THAT(t, Catch::Matchers::WithinAbs(0.59447, epsilon));
    bezier::test::fuzzyCheckPoint(point, 109.50371, 116.41393);

    bezier::Bezier<3> c({ {210, 160}, {35, 200}, {220, 260}, {220, 60} });
    t = c.archMidPoint();
    point = c.valueAt(t);
    CHECK_THAT(t, Catch::Matchers::WithinAbs(0.66141, epsilon));
    bezier::test::fuzzyCheckPoint(point, 177.52785, 184.60152);

    bezier::Bezier<3> d({ {170, 90}, {100, 200}, {40, 40}, {230, 135} });
    t = d.archMidPoint();
    point = d.valueAt(t);
    CHECK_THAT(t, Catch::Matchers::WithinAbs(0.702915192, epsilon));
    bezier::test::fuzzyCheckPoint(point, 120.56327, 104.08348);

    // ---

    bezier::Bezier<3> cubicBezier({ { 120, 160 }, { 35, 200 }, { 220, 260 }, {220, 40} });

    t = cubicBezier.archMidPoint();
    point = cubicBezier.valueAt(t);
    CHECK_THAT(t, Catch::Matchers::WithinAbs(0.70718, epsilon));
    bezier::test::fuzzyCheckPoint(point, 183.83701, 168.76790);

    // High epsilon, high max search depth.
    t = cubicBezier.archMidPoint(1e-8f, 1000);
    point = cubicBezier.valueAt(t);
    CHECK_THAT(t, Catch::Matchers::WithinAbs(0.70718, epsilon));
    bezier::test::fuzzyCheckPoint(point, 183.83712, 168.76769);

    // High epsilon, low max search depth. Will not be precise.
    t = cubicBezier.archMidPoint(1e-8f, 10);
    point = cubicBezier.valueAt(t);
    CHECK_THAT(t, Catch::Matchers::WithinAbs(0.70752, epsilon));
    bezier::test::fuzzyCheckPoint(point, 183.90683, 168.68553);

    // Low epsilon, high max search depth. Will not be precise.
    t = cubicBezier.archMidPoint(0.1f, 1000);
    point = cubicBezier.valueAt(t);
    CHECK_THAT(t, Catch::Matchers::WithinAbs(0.70703, epsilon));
    bezier::test::fuzzyCheckPoint(point, 183.80527, 168.80531);

    // Low epsilon, low max search depth. Will not be precise.
    t = cubicBezier.archMidPoint(0.1f, 10);
    point = cubicBezier.valueAt(t);
    CHECK_THAT(t, Catch::Matchers::WithinAbs(0.70703, epsilon));
    bezier::test::fuzzyCheckPoint(point, 183.80527, 168.80531);
}

// The test that exists in README.md, because it should be correct.
TEST_CASE("Test README examples", "[readme]")
{
    static constexpr float epsilon = 1.0e-4f;

    // Create a cubic bezier with 4 points. Visualized at https://www.desmos.com/calculator/fivneeogmh
    bezier::Bezier<3> cubicBezier({ {120, 160}, {35, 200}, {220, 260}, {220, 40} });

    // Get coordinates on the curve from a value between 0 and 1 (values outside this range are also valid because of the way bezier curves are defined).
    bezier::Point p;
    p = cubicBezier.valueAt(0);     // (120, 60)
    bezier::test::fuzzyCheckPoint(p, 120.0, 160.0);
    p = cubicBezier.valueAt(0.5);   // (138.125, 197.5)
    bezier::test::fuzzyCheckPoint(p, 138.125, 197.5);

    // Get coordinate values for a single axis. Currently only supports 2D.
    float value;
    value = cubicBezier.valueAt(1, 0);    // 220 (x-coordinate at t = 1)
    CHECK_THAT(value, Catch::Matchers::WithinAbs(220.0, epsilon));
    value = cubicBezier.valueAt(0.75, 1); // 157.1875 (y-coordinate at t = 0.75)
    CHECK_THAT(value, Catch::Matchers::WithinAbs(157.1875, epsilon));
    value = cubicBezier.length();         // 272.85 (Arc length of the bezier curve)
    CHECK_THAT(value, Catch::Matchers::WithinAbs(272.853, epsilon));

    // Translate and rotate bezier curves.
    bezier::Bezier<3> copy = cubicBezier;
    copy.translate(10, 15);      // Translate 10 in x-direction, 15 in y-direction
    CHECK_THAT(copy.valueAt(0, 0), Catch::Matchers::WithinAbs(130.0, epsilon));
    CHECK_THAT(copy.valueAt(0, 1), Catch::Matchers::WithinAbs(175.0, epsilon));
    copy.rotate(0.5);             // Rotate 0.5 radians around the origin
    copy.rotate(3.14f, {-5, 20}); // Rotate 3.14 radians around (-5, 20)

    // Get normals along the bezier curve.
    bezier::Normal normal = cubicBezier.normalAt(0.75); // Get normalized normal at t = 0.75. Add false as second argument to disable normalization.
    float angle = normal.angle();       // Angle in radians
    float angleDeg = normal.angleDeg(); // Angle in degrees
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(0.83892852, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.544241607, epsilon));
    CHECK_THAT(angle, Catch::Matchers::WithinAbs(0.575484872, epsilon));
    CHECK_THAT(angleDeg, Catch::Matchers::WithinAbs(32.9728546, epsilon));

    // Get tangents along the bezier curve.
    bezier::Tangent tangent = cubicBezier.tangentAt(0.25); // Get normalized tangent at t = 0.25. Add false as second argument to disable normalization.
    angle = tangent.angle();       // Angle in radians
    angleDeg = tangent.angleDeg(); // Angle in degrees
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.567925274, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(0.823080122, epsilon));
    CHECK_THAT(angle, Catch::Matchers::WithinAbs(0.966813385, epsilon));
    CHECK_THAT(angleDeg, Catch::Matchers::WithinAbs(55.3943253, epsilon));

    // Get derivatives of the bezier curve, resulting in a bezier curve of one order less.
    bezier::Bezier<2> db  = cubicBezier.derivative(); // First derivative
    bezier::Bezier<1> ddb = db.derivative();          // Second derivative
    bezier::test::fuzzyCheckPoint(db[0], -255.0, 120.0);
    bezier::test::fuzzyCheckPoint(db[1], 555.0, 180.0);
    bezier::test::fuzzyCheckPoint(db[2], 0.0, -660.0);
    bezier::test::fuzzyCheckPoint(ddb[0], 1620.0, 120.0);
    bezier::test::fuzzyCheckPoint(ddb[1], -1110.0, -1680.0);

    // Get extreme values of the bezier curves.
    bezier::ExtremeValues xVals = cubicBezier.derivativeZero();  // Contains 3 extreme value locations: t = 0.186811984, t = 1.0 and t = 0.437850952
    CHECK(xVals.size() == 3);
    CHECK_THAT(xVals[0].t, Catch::Matchers::WithinAbs(0.186811984, epsilon));
    CHECK_THAT(xVals[1].t, Catch::Matchers::WithinAbs(1.0, epsilon));
    CHECK_THAT(xVals[2].t, Catch::Matchers::WithinAbs(0.437850952, epsilon));
    bezier::ExtremeValue const& xVal = xVals[0];                 // Contains t value and axis for the first extreme value
    bezier::Point xValCoord = cubicBezier.valueAt(xVal.t);       // Get the coordinates for the first extreme value (97.6645355, 182.55565)
    CHECK_THAT(xValCoord.x, Catch::Matchers::WithinAbs(97.6645355, epsilon));
    CHECK_THAT(xValCoord.y, Catch::Matchers::WithinAbs(182.555649, epsilon));
    bezier::ExtremePoints xPoints = cubicBezier.extremePoints(); // Or get all the extreme points directly (includes 0 and 1)
    bezier::test::fuzzyCheckPoint(xPoints[0], 97.6645355, 182.55565);
    bezier::test::fuzzyCheckPoint(xPoints[1], 220.0, 40.0);
    bezier::test::fuzzyCheckPoint(xPoints[2], 125.442337, 198.86235);
    bezier::test::fuzzyCheckPoint(xPoints[3], 120.0, 160.0);

    // Get bounding boxes of the bezier curves.
    bezier::AABB aabb = cubicBezier.aabb();             // Axis Aligned Bounding Box
    CHECK(aabb.size() == 4);
    CHECK_THAT(aabb.minX(), Catch::Matchers::WithinAbs(97.6645355, epsilon));
    CHECK_THAT(aabb.maxX(), Catch::Matchers::WithinAbs(220.0, epsilon));
    CHECK_THAT(aabb.minY(), Catch::Matchers::WithinAbs(40.0, epsilon));
    CHECK_THAT(aabb.maxY(), Catch::Matchers::WithinAbs(198.86235, epsilon));
    CHECK_THAT(aabb.width(), Catch::Matchers::WithinAbs(122.335464, epsilon));
    CHECK_THAT(aabb.height(), Catch::Matchers::WithinAbs(158.86235, epsilon));
    CHECK_THAT(aabb.area(), Catch::Matchers::WithinAbs(19434.5, epsilon));
    aabb = cubicBezier.aabb(xPoints);                   // Or get from extreme points (if you already have them) to reduce calculation time
    CHECK(aabb.size() == 4);
    CHECK_THAT(aabb.minX(), Catch::Matchers::WithinAbs(97.6645355, epsilon));
    CHECK_THAT(aabb.maxX(), Catch::Matchers::WithinAbs(220.0, epsilon));
    CHECK_THAT(aabb.minY(), Catch::Matchers::WithinAbs(40.0, epsilon));
    CHECK_THAT(aabb.maxY(), Catch::Matchers::WithinAbs(198.86235, epsilon));
    CHECK_THAT(aabb.width(), Catch::Matchers::WithinAbs(122.335464, epsilon));
    CHECK_THAT(aabb.height(), Catch::Matchers::WithinAbs(158.86235, epsilon));
    CHECK_THAT(aabb.area(), Catch::Matchers::WithinAbs(19434.5, epsilon));
    bezier::TightBoundingBox tbb = cubicBezier.tbb();   // Tight bounding box
    CHECK(tbb.size() == 4);
    CHECK_THAT(tbb.minX(), Catch::Matchers::WithinAbs(92.568962, epsilon));
    CHECK_THAT(tbb.maxX(), Catch::Matchers::WithinAbs(261.989441, epsilon));
    CHECK_THAT(tbb.minY(), Catch::Matchers::WithinAbs(36.2565613, epsilon));
    CHECK_THAT(tbb.maxY(), Catch::Matchers::WithinAbs(222.517883, epsilon));
    CHECK_THAT(tbb.width(), Catch::Matchers::WithinAbs(60.5054359, epsilon));
    CHECK_THAT(tbb.height(), Catch::Matchers::WithinAbs(192.036713, epsilon));
    CHECK_THAT(tbb.area(), Catch::Matchers::WithinAbs(11619.2646, epsilon));

    // Split the bezier curve at desired points. The left and right parts are new bezier curves
    // of the same order as the original curve.
    auto split = cubicBezier.split(0.5f);
    bezier::test::fuzzyCheckPoint(split.left[0], 120.0, 160.0);
    bezier::test::fuzzyCheckPoint(split.left[1], 77.5, 180.0);
    bezier::test::fuzzyCheckPoint(split.left[2], 102.5, 205.0);
    bezier::test::fuzzyCheckPoint(split.left[3], 138.125, 197.5);
    bezier::test::fuzzyCheckPoint(split.right[0], 220.0, 40.0);
    bezier::test::fuzzyCheckPoint(split.right[1], 220.0, 150.0);
    bezier::test::fuzzyCheckPoint(split.right[2], 173.75, 190.0);
    bezier::test::fuzzyCheckPoint(split.right[3], 138.125, 197.5);
    CHECK(split.left.order() == cubicBezier.order());
    CHECK(split.right.order() == cubicBezier.order());

    // Find the mid point on the curve by arch length.
    float tAtMidPoint = cubicBezier.archMidPoint();
    bezier::Point midPoint = cubicBezier.valueAt(tAtMidPoint);
    CHECK_THAT(tAtMidPoint, Catch::Matchers::WithinAbs(0.70718, epsilon));
    bezier::test::fuzzyCheckPoint(midPoint, 183.83701, 168.76790);
}
