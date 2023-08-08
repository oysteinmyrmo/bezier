#include "test_beziers.h"

// Visualization: https://www.desmos.com/calculator/fivneeogmh
bezier::Bezier<3> bezier::test::defaultCubicBezier()
{
    return ::bezier::Bezier<3>({
        {120, 160},
        {35,  200},
        {220, 260},
        {220,  40}
    });
}

bezier::Bezier<2> bezier::test::defaultQuadraticBezier()
{
    return ::bezier::Bezier<2>({
        {70, 155},
        {20, 110},
        {100, 75}
    });
}
