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

TEST_CASE("Test derivatives", "[derivatives]")
{
    bezier::Bezier<3> bezier3 = bezier::test::defaultCubicBezier();
    bezier::Bezier<2> bezier2 = bezier3.derivative();
    bezier::Bezier<1> bezier1 = bezier2.derivative();
    bezier::Bezier<0> bezier0 = bezier1.derivative();

    CHECK(bezier3.size() == 4);
    CHECK(bezier2.size() == 3);
    CHECK(bezier1.size() == 2);
    CHECK(bezier0.size() == 1);

    bezier::test::fuzzyCheckPoint(bezier2[0], -255.0, 120.0);
    bezier::test::fuzzyCheckPoint(bezier2[1], 555.0, 180.0);
    bezier::test::fuzzyCheckPoint(bezier2[2], 0.0, -660.0);

    bezier::test::fuzzyCheckPoint(bezier1[0], 1620.0, 120.0);
    bezier::test::fuzzyCheckPoint(bezier1[1], -1110.0, -1680.0);

    bezier::test::fuzzyCheckPoint(bezier0[0], -2730.0, -1800.0);

    bezier2 = bezier::test::defaultQuadraticBezier();
    bezier1 = bezier2.derivative();
    bezier0 = bezier1.derivative();

    CHECK(bezier2.size() == 3);
    CHECK(bezier1.size() == 2);
    CHECK(bezier0.size() == 1);

    bezier::test::fuzzyCheckPoint(bezier1[0], -100.0, -90.0);
    bezier::test::fuzzyCheckPoint(bezier1[1], 160.0, -70.0);

    bezier::test::fuzzyCheckPoint(bezier0[0], 260.0, 20.0);
}

TEST_CASE("Test extreme values", "[extreme_values]")
{
    static constexpr double epsilon = 1.0e-6;

    bezier::Bezier<3> bezier3 = bezier::test::defaultCubicBezier();

    bezier::ExtremeValues xVals = bezier3.derivativeZero();
    CHECK(xVals.size() == 3);
    CHECK_THAT(xVals[0].t, Catch::Matchers::WithinAbs(0.186813, epsilon));
    CHECK_THAT(xVals[1].t, Catch::Matchers::WithinAbs(1.0, epsilon));
    CHECK_THAT(xVals[2].t, Catch::Matchers::WithinAbs(0.437850952, epsilon));

    bezier::ExtremePoints xPoints = bezier3.extremePoints();
    CHECK(xPoints.size() == 4);
    bezier::test::fuzzyCheckPoint(xPoints[0], 97.664533, 182.555645);
    bezier::test::fuzzyCheckPoint(xPoints[1], 220.0, 40.0);
    bezier::test::fuzzyCheckPoint(xPoints[2], 125.442334, 198.862345);
    bezier::test::fuzzyCheckPoint(xPoints[3], 120.0, 160.0);

    bezier::AABB aabb = bezier3.aabb();
    CHECK(aabb.size() == 4);
    CHECK_THAT(aabb.minX(), Catch::Matchers::WithinAbs(97.664533, epsilon));
    CHECK_THAT(aabb.maxX(), Catch::Matchers::WithinAbs(220.0, epsilon));
    CHECK_THAT(aabb.minY(), Catch::Matchers::WithinAbs(40.0, epsilon));
    CHECK_THAT(aabb.maxY(), Catch::Matchers::WithinAbs(198.862345, epsilon));
    CHECK_THAT(aabb.width(), Catch::Matchers::WithinAbs(122.335466, epsilon));
    CHECK_THAT(aabb.height(), Catch::Matchers::WithinAbs(158.862345, epsilon));
    CHECK_THAT(aabb.area(), Catch::Matchers::WithinAbs(19434.499222, epsilon));

    bezier::TBB tbb = bezier3.tbb();
    CHECK(tbb.size() == 4);
    CHECK_THAT(tbb.minX(), Catch::Matchers::WithinAbs(92.568952, epsilon));
    CHECK_THAT(tbb.maxX(), Catch::Matchers::WithinAbs(261.989423, epsilon));
    CHECK_THAT(tbb.minY(), Catch::Matchers::WithinAbs(36.256559, epsilon));
    CHECK_THAT(tbb.maxY(), Catch::Matchers::WithinAbs(222.517888, epsilon));
    CHECK_THAT(tbb.width(), Catch::Matchers::WithinAbs(60.505421, epsilon));
    CHECK_THAT(tbb.height(), Catch::Matchers::WithinAbs(192.036729, epsilon));
    CHECK_THAT(tbb.area(), Catch::Matchers::WithinAbs(11619.263247, epsilon));

    bezier::Bezier<2> bezier2 = bezier::test::defaultQuadraticBezier();

    xVals = bezier2.derivativeZero();
    CHECK(xVals.size() == 1);
    CHECK_THAT(xVals[0].t, Catch::Matchers::WithinAbs(0.384615391, epsilon));

    xPoints = bezier2.extremePoints();
    CHECK(xPoints.size() == 3);
    bezier::test::fuzzyCheckPoint(xPoints[0], 50.769230, 121.863905);
    bezier::test::fuzzyCheckPoint(xPoints[1], 70.0, 155.0);
    bezier::test::fuzzyCheckPoint(xPoints[2], 100.0, 75.0);

    aabb = bezier2.aabb(xPoints);
    CHECK(aabb.size() == 4);
    CHECK_THAT(aabb.minX(), Catch::Matchers::WithinAbs(50.769230, epsilon));
    CHECK_THAT(aabb.maxX(), Catch::Matchers::WithinAbs(100.0, epsilon));
    CHECK_THAT(aabb.minY(), Catch::Matchers::WithinAbs(75.0, epsilon));
    CHECK_THAT(aabb.maxY(), Catch::Matchers::WithinAbs(155.0, epsilon));
    CHECK_THAT(aabb.width(), Catch::Matchers::WithinAbs(49.230769, epsilon));
    CHECK_THAT(aabb.height(), Catch::Matchers::WithinAbs(80.0, epsilon));
    CHECK_THAT(aabb.area(), Catch::Matchers::WithinAbs(3938.461538, epsilon));

    tbb = bezier2.tbb();
    CHECK(tbb.size() == 4);
    CHECK_THAT(tbb.minX(), Catch::Matchers::WithinAbs(40.684931, epsilon));
    CHECK_THAT(tbb.maxX(), Catch::Matchers::WithinAbs(100.0, epsilon));
    CHECK_THAT(tbb.minY(), Catch::Matchers::WithinAbs(64.006849, epsilon));
    CHECK_THAT(tbb.maxY(), Catch::Matchers::WithinAbs(155.0, epsilon));
    CHECK_THAT(tbb.width(), Catch::Matchers::WithinAbs(31.308506, epsilon));
    CHECK_THAT(tbb.height(), Catch::Matchers::WithinAbs(85.440037, epsilon));
    CHECK_THAT(tbb.area(), Catch::Matchers::WithinAbs(2675.0, epsilon));
}

TEST_CASE("Test tangents", "[curves][tangents]")
{
    static constexpr double epsilon = 1.0e-6;

    bezier::Bezier<3> bezier3 = bezier::test::defaultCubicBezier();
    bezier::ExtremeValues xVals = bezier3.derivativeZero();
    bezier::Tangent tangent;
    CHECK(xVals.size() == 3);

    tangent = bezier3.tangentAt(0.0);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(-0.904818713, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(0.425797045, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(2.70175004, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(154.798876, epsilon));

    tangent = bezier3.tangentAt(0.25);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.567925274, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(0.823080122, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(0.966813385, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(55.3943253, epsilon));

    tangent = bezier3.tangentAt(0.50);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.978549778, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(-0.206010476, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(-0.207496226, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(-11.8886576, epsilon));

    tangent = bezier3.tangentAt(0.75);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.544241607, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(-0.83892852, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(-0.995311498, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(-57.027147, epsilon));

    tangent = bezier3.tangentAt(0.666);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.738803029, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(-0.673921466, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(-0.73950386, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(-42.370450, epsilon));

    tangent = bezier3.tangentAt(0.333);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.911237537, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(0.411881238, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(0.424517602, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(24.323066, epsilon));

    tangent = bezier3.tangentAt(xVals[0].t);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(1.0, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(bezier::internal::pi / 2.0, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(90.0, epsilon));

    tangent = bezier3.tangentAt(xVals[1].t);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(-1.0, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(-bezier::internal::pi / 2.0, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(-90.0, epsilon));

    tangent = bezier3.tangentAt(xVals[2].t);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(1.0, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(0.0, epsilon));
}

TEST_CASE("Test normals", "[curves][normals]")
{
    static constexpr double epsilon = 1.0e-6;

    bezier::Bezier<3> bezier3 = bezier::test::defaultCubicBezier();
    bezier::ExtremeValues xVals = bezier3.derivativeZero();
    bezier::Normal normal;
    CHECK(xVals.size() == 3);

    normal = bezier3.normalAt(0.0);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(-0.425797045, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(-0.904818713, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(-2.01063895, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(-115.201123, epsilon));

    normal = bezier3.normalAt(0.25);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(-0.823080122, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.567925274, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(2.53760958, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(145.394324, epsilon));

    normal = bezier3.normalAt(0.50);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(0.206010476, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.978549778, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(1.36330009, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(78.111341, epsilon));

    normal = bezier3.normalAt(0.75);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(0.83892852, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.544241607, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(0.575484872, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(32.972852, epsilon));

    normal = bezier3.normalAt(0.666);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(0.673921466, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.738803029, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(0.83129245, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(47.629550, epsilon));

    normal = bezier3.normalAt(0.333);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(-0.411881238, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.911237537, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(1.99531388, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(114.323066, epsilon));

    normal = bezier3.normalAt(xVals[0].t);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(-1.0, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(-bezier::internal::pi, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(-180.0, epsilon));

    normal = bezier3.normalAt(xVals[1].t);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(1.0, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(0.0, epsilon));

    normal = bezier3.normalAt(xVals[2].t);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(1.0, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(bezier::internal::pi / 2.0, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(90.0, epsilon));
}
