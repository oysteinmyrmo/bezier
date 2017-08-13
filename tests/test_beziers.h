#pragma once
#include "bezier.h"
#include <vector>

namespace TestBeziers
{
    namespace Creators
    {
        // Visualization: https://www.desmos.com/calculator/5i8ce3s7lq
        Bezier::Bezier<3> defaultCubicBezier()
        {
            std::vector<Bezier::Point> controlPoints(4);
            controlPoints[0] = Bezier::Point(120, 160);
            controlPoints[1] = Bezier::Point(35, 200);
            controlPoints[2] = Bezier::Point(220, 260);
            controlPoints[3] = Bezier::Point(220, 40);

            return Bezier::Bezier<3>(controlPoints);
        }
        
        Bezier::Bezier<2> defaultQuadraticBezier()
        {
            std::vector<Bezier::Point> controlPoints(3);
            controlPoints[0].set(70, 155);
            controlPoints[1].set(20, 110);
            controlPoints[2].set(100, 75);
            return Bezier::Bezier<2>(controlPoints);
        }
    }

    namespace Default
    {
        static const Bezier::Bezier<2> QuadraticBezier = Creators::defaultQuadraticBezier();
        static const Bezier::Bezier<3> CubicBezier = Creators::defaultCubicBezier();
    }
}
