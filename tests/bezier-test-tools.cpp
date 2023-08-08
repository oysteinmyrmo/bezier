#include "bezier-test-tools.h"

void bezier::test::fuzzyCheckPoint(const ::bezier::Point p, const double x, const double y, const double epsilon)
{
    INFO("Failure: fuzzyCheckPoint((" << p.x << "," << p.y << "), " << x << ", " << y << ", " << epsilon << ");");
    CHECK_THAT(p.x, Catch::Matchers::WithinAbs(x, epsilon));
    CHECK_THAT(p.y, Catch::Matchers::WithinAbs(y, epsilon));
}
