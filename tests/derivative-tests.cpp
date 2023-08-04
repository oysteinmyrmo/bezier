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
#include "bezier-test-tools.h"
#include "test_beziers.h"

TEST_CASE("Test derivatives", "[derivatives]")
{
    Bezier::Bezier<3> bezier3 = Bezier::Test::defaultCubicBezier();
    Bezier::Bezier<2> bezier2 = bezier3.derivative();
    Bezier::Bezier<1> bezier1 = bezier2.derivative();
    Bezier::Bezier<0> bezier0 = bezier1.derivative();

    CHECK(bezier3.size() == 4);
    CHECK(bezier2.size() == 3);
    CHECK(bezier1.size() == 2);
    CHECK(bezier0.size() == 1);

    Bezier::Test::fuzzyCheckPoint(bezier2[0], -255.0, 120.0);
    Bezier::Test::fuzzyCheckPoint(bezier2[1], 555.0, 180.0);
    Bezier::Test::fuzzyCheckPoint(bezier2[2], 0.0, -660.0);

    Bezier::Test::fuzzyCheckPoint(bezier1[0], 1620.0, 120.0);
    Bezier::Test::fuzzyCheckPoint(bezier1[1], -1110.0, -1680.0);

    Bezier::Test::fuzzyCheckPoint(bezier0[0], -2730.0, -1800.0);

    bezier2 = Bezier::Test::defaultQuadraticBezier();
    bezier1 = bezier2.derivative();
    bezier0 = bezier1.derivative();

    CHECK(bezier2.size() == 3);
    CHECK(bezier1.size() == 2);
    CHECK(bezier0.size() == 1);

    Bezier::Test::fuzzyCheckPoint(bezier1[0], -100.0, -90.0);
    Bezier::Test::fuzzyCheckPoint(bezier1[1], 160.0, -70.0);

    Bezier::Test::fuzzyCheckPoint(bezier0[0], 260.0, 20.0);
}

TEST_CASE("Test extreme values", "[extreme_values]")
{
    static constexpr float epsilon = 1.0e-4f;

    Bezier::Bezier<3> bezier3 = Bezier::Test::defaultCubicBezier();

    Bezier::ExtremeValues xVals = bezier3.derivativeZero();
    CHECK(xVals.size() == 3);
    CHECK_THAT(xVals[0].t, Catch::Matchers::WithinAbs(0.186811984, epsilon));
    CHECK_THAT(xVals[1].t, Catch::Matchers::WithinAbs(1.0, epsilon));
    CHECK_THAT(xVals[2].t, Catch::Matchers::WithinAbs(0.437850952, epsilon));

    Bezier::ExtremePoints xPoints = bezier3.extremePoints();
    CHECK(xPoints.size() == 4);
    Bezier::Test::fuzzyCheckPoint(xPoints[0], 97.6645355, 182.555649);
    Bezier::Test::fuzzyCheckPoint(xPoints[1], 220.0, 40.0);
    Bezier::Test::fuzzyCheckPoint(xPoints[2], 125.442337, 198.86235);
    Bezier::Test::fuzzyCheckPoint(xPoints[3], 120.0, 160.0);

    Bezier::AABB aabb = bezier3.aabb();
    CHECK(aabb.size() == 4);
    CHECK_THAT(aabb.minX(), Catch::Matchers::WithinAbs(97.6645355, epsilon));
    CHECK_THAT(aabb.maxX(), Catch::Matchers::WithinAbs(220.0, epsilon));
    CHECK_THAT(aabb.minY(), Catch::Matchers::WithinAbs(40.0, epsilon));
    CHECK_THAT(aabb.maxY(), Catch::Matchers::WithinAbs(198.86235, epsilon));
    CHECK_THAT(aabb.width(), Catch::Matchers::WithinAbs(122.335464, epsilon));
    CHECK_THAT(aabb.height(), Catch::Matchers::WithinAbs(158.86235, epsilon));
    CHECK_THAT(aabb.area(), Catch::Matchers::WithinAbs(19434.5, epsilon));

    Bezier::TBB tbb = bezier3.tbb();
    CHECK(tbb.size() == 4);
    CHECK_THAT(tbb.minX(), Catch::Matchers::WithinAbs(92.568962, epsilon));
    CHECK_THAT(tbb.maxX(), Catch::Matchers::WithinAbs(261.989441, epsilon));
    CHECK_THAT(tbb.minY(), Catch::Matchers::WithinAbs(36.2565613, epsilon));
    CHECK_THAT(tbb.maxY(), Catch::Matchers::WithinAbs(222.517883, epsilon));
    CHECK_THAT(tbb.width(), Catch::Matchers::WithinAbs(60.5054359, epsilon));
    CHECK_THAT(tbb.height(), Catch::Matchers::WithinAbs(192.036713, epsilon));
    CHECK_THAT(tbb.area(), Catch::Matchers::WithinAbs(11619.2646, epsilon));

    Bezier::Bezier<2> bezier2 = Bezier::Test::defaultQuadraticBezier();

    xVals = bezier2.derivativeZero();
    CHECK(xVals.size() == 1);
    CHECK_THAT(xVals[0].t, Catch::Matchers::WithinAbs(0.384615391, epsilon));

    xPoints = bezier2.extremePoints();
    CHECK(xPoints.size() == 3);
    Bezier::Test::fuzzyCheckPoint(xPoints[0], 50.7692261, 121.863899);
    Bezier::Test::fuzzyCheckPoint(xPoints[1], 70.0, 155.0);
    Bezier::Test::fuzzyCheckPoint(xPoints[2], 100.0, 75.0);

    aabb = bezier2.aabb(xPoints);
    CHECK(aabb.size() == 4);
    CHECK_THAT(aabb.minX(), Catch::Matchers::WithinAbs(50.7692261, epsilon));
    CHECK_THAT(aabb.maxX(), Catch::Matchers::WithinAbs(100.0, epsilon));
    CHECK_THAT(aabb.minY(), Catch::Matchers::WithinAbs(75.0, epsilon));
    CHECK_THAT(aabb.maxY(), Catch::Matchers::WithinAbs(155.0, epsilon));
    CHECK_THAT(aabb.width(), Catch::Matchers::WithinAbs(49.2307739, epsilon));
    CHECK_THAT(aabb.height(), Catch::Matchers::WithinAbs(80.0, epsilon));
    CHECK_THAT(aabb.area(), Catch::Matchers::WithinAbs(3938.46191, epsilon));

    tbb = bezier2.tbb();
    CHECK(tbb.size() == 4);
    CHECK_THAT(tbb.minX(), Catch::Matchers::WithinAbs(40.6849289, epsilon));
    CHECK_THAT(tbb.maxX(), Catch::Matchers::WithinAbs(100.0, epsilon));
    CHECK_THAT(tbb.minY(), Catch::Matchers::WithinAbs(64.0068511, epsilon));
    CHECK_THAT(tbb.maxY(), Catch::Matchers::WithinAbs(155.0, epsilon));
    CHECK_THAT(tbb.width(), Catch::Matchers::WithinAbs(31.3085079, epsilon));
    CHECK_THAT(tbb.height(), Catch::Matchers::WithinAbs(85.4400406, epsilon));
    CHECK_THAT(tbb.area(), Catch::Matchers::WithinAbs(2674.99951, epsilon));
}

TEST_CASE("Test tangents", "[curves][tangents]")
{
    static constexpr float epsilon = 1.0e-1f;

    Bezier::Bezier<3> bezier3 = Bezier::Test::defaultCubicBezier();
    Bezier::ExtremeValues xVals = bezier3.derivativeZero();
    Bezier::Tangent tangent;
    CHECK(xVals.size() == 3);

    tangent = bezier3.tangentAt(0.0f);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(-0.904818713, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(0.425797045, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(2.70175004, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(154.798874, epsilon));

    tangent = bezier3.tangentAt(0.25f);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.567925274, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(0.823080122, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(0.966813385, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(55.3943253, epsilon));

    tangent = bezier3.tangentAt(0.50f);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.978549778, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(-0.206010476, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(-0.207496226, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(-11.8886576, epsilon));

    tangent = bezier3.tangentAt(0.75f);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.544241607, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(-0.83892852, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(-0.995311498, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(-57.0271492, epsilon));

    tangent = bezier3.tangentAt(0.666f);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.738803029, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(-0.673921466, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(-0.73950386, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(-42.3704491, epsilon));

    tangent = bezier3.tangentAt(0.333f);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.911237537, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(0.411881238, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(0.424517602, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(24.3230667, epsilon));

    tangent = bezier3.tangentAt(xVals[0].t);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(1.0, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(Bezier::Math::PI / 2.0, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(90.0, epsilon));

    tangent = bezier3.tangentAt(xVals[1].t);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(-1.0, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(-Bezier::Math::PI / 2.0, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(-90.0, epsilon));

    tangent = bezier3.tangentAt(xVals[2].t);
    CHECK_THAT(tangent.x, Catch::Matchers::WithinAbs(1.0, epsilon));
    CHECK_THAT(tangent.y, Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(tangent.angle(), Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(tangent.angleDeg(), Catch::Matchers::WithinAbs(0.0, epsilon));
}

TEST_CASE("Test normals", "[curves][normals]")
{
    static constexpr double epsilon = 1.0e-4;

    Bezier::Bezier<3> bezier3 = Bezier::Test::defaultCubicBezier();
    Bezier::ExtremeValues xVals = bezier3.derivativeZero();
    Bezier::Normal normal;
    CHECK(xVals.size() == 3);

    normal = bezier3.normalAt(0.0);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(-0.425797045, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(-0.904818713, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(-2.01063895, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(-115.201126, epsilon));

    normal = bezier3.normalAt(0.25);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(-0.823080122, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.567925274, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(2.53760958, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(145.394318, epsilon));

    normal = bezier3.normalAt(0.50);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(0.206010476, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.978549778, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(1.36330009, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(78.1113433, epsilon));

    normal = bezier3.normalAt(0.75);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(0.83892852, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.544241607, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(0.575484872, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(32.9728546, epsilon));

    normal = bezier3.normalAt(0.666);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(0.673921466, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.738803029, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(0.83129245, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(47.6295471, epsilon));

    normal = bezier3.normalAt(0.333);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(-0.411881238, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.911237537, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(1.99531388, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(114.323067, epsilon));

    normal = bezier3.normalAt(xVals[0].t);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(-1.0, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(-Bezier::Math::PI, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(-180.0, epsilon));

    normal = bezier3.normalAt(xVals[1].t);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(1.0, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(0.0, epsilon));

    normal = bezier3.normalAt(xVals[2].t);
    CHECK_THAT(normal.x, Catch::Matchers::WithinAbs(0.0, epsilon));
    CHECK_THAT(normal.y, Catch::Matchers::WithinAbs(1.0, epsilon));
    CHECK_THAT(normal.angle(), Catch::Matchers::WithinAbs(Bezier::Math::PI / 2.0, epsilon));
    CHECK_THAT(normal.angleDeg(), Catch::Matchers::WithinAbs(90.0, epsilon));
}
