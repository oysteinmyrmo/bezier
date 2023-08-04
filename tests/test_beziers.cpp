#include "test_beziers.h"

// Visualization: https://www.desmos.com/calculator/fivneeogmh
Bezier::Bezier<3> Bezier::Test::defaultCubicBezier()
{
    return ::Bezier::Bezier<3>({
        {120, 160},
        {35,  200},
        {220, 260},
        {220,  40}
    });
}

Bezier::Bezier<2> Bezier::Test::defaultQuadraticBezier()
{
    return ::Bezier::Bezier<2>({
        {70, 155},
        {20, 110},
        {100, 75}
    });
}
