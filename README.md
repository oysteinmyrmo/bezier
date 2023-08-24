# Bezier

Bezier is a single header only C++11 library for bezier curve calculations and manipulations. Currently only supports 2D bezier curves.

## Include Bezier in Your Project

If it is desirable to use the single header file directly, simply download and include it, for example `curl -O https://raw.githubusercontent.com/oysteinmyrmo/bezier/master/include/bezier.h`.

It is also easy using CMake's `FetchContent` functionality:

```c++
include(FetchContent)

FetchContent_Declare(
    bezier
    GIT_REPOSITORY https://github.com/oysteinmyrmo/bezier.git
    GIT_TAG        v0.2.0
)

set(BEZIER_TESTS OFF) # Default ON
FetchContent_MakeAvailable(bezier)

...

target_link_libraries(some_target PRIVATE bezier)
```

When this is done the library can be included by doing `#include <bezier/bezier.h>`.

## General Usage

The following examples demonstrate how to use the library. In this context, `t` is the parametrized factor defining the bezier curve, ranging from 0 to 1. Even though the bezier curve is defined to be between `t = 0` and `t = 1`, there is nothing wrong with using other values for `t`, the results will only be outside the normal range of the bezier curve.

```c++
// Create a cubic bezier with 4 points. Visualized at https://www.desmos.com/calculator/fivneeogmh
bezier::Bezier<3> cubicBezier({ {120, 160}, {35, 200}, {220, 260}, {220, 40} });

// Get coordinates on the curve from a value between 0 and 1 (values outside this range are also valid because of the way bezier curves are defined).
bezier::Point p;
p = cubicBezier.valueAt(0);   // (120, 160)
p = cubicBezier.valueAt(0.5); // (138.125, 197.5)

// Get coordinate values for a single axis. Currently only supports 2D.
double value;
value = cubicBezier.valueAt(1, 0);    // 220 (x-coordinate at t = 1)
value = cubicBezier.valueAt(0.75, 1); // 157.1875 (y-coordinate at t = 0.75)
value = cubicBezier.length();         // 272.85 (Arc length of the bezier curve)

// Translate and rotate bezier curves.
bezier::Bezier<3> copy = cubicBezier;
copy.translate(10, 15);      // Translate 10 in x-direction, 15 in y-direction
copy.rotate(0.5);            // Rotate 0.5 radians around the origin
copy.rotate(3.14, {-5, 20}); // Rotate 3.14 radians around (-5, 20)

// Get normals along the bezier curve.
bezier::Normal normal = cubicBezier.normalAt(0.75); // Get normalized normal at t = 0.75. Add false as second argument to disable normalization.
double angle = normal.angle();       // Angle in radians
double angleDeg = normal.angleDeg(); // Angle in degrees

// Get tangents along the bezier curve.
bezier::Tangent tangent = cubicBezier.tangentAt(0.25); // Get normalized tangent at t = 0.25. Add false as second argument to disable normalization.
angle = tangent.angle();       // Angle in radians
angleDeg = tangent.angleDeg(); // Angle in degrees

// Get derivatives of the bezier curve, resulting in a bezier curve of one order less.
bezier::Bezier<2> db  = cubicBezier.derivative(); // First derivative
bezier::Bezier<1> ddb = db.derivative();          // Second derivative

// Get extreme values of the bezier curves.
bezier::ExtremeValues xVals = cubicBezier.derivativeZero();  // Contains 3 extreme value locations: t = 0.186811984, t = 1.0 and t = 0.437850952
bezier::ExtremeValue const& xVal = xVals[0];                 // Contains t value and axis for the first extreme value
bezier::Point xValCoord = cubicBezier.valueAt(xVal.t);       // Get the coordinates for the first extreme value (97.6645355, 182.55565)
bezier::ExtremePoints xPoints = cubicBezier.extremePoints(); // Or get all the extreme points directly (includes 0 and 1)

// Get bounding boxes of the bezier curves.
bezier::AABB aabb = cubicBezier.aabb();            // Axis Aligned Bounding Box
aabb = cubicBezier.aabb(xPoints);                  // Or get from extreme points (if you already have them) to reduce calculation time
bezier::TightBoundingBox tbb = cubicBezier.tbb();  // Tight bounding box

// Split the bezier curve at desired points. The left and right parts are new bezier curves
// of the same order as the original curve.
auto split = cubicBezier.split(0.5);
auto &left  = split.left;  // Left part of the split
auto &right = split.right; // Right part of the split

// Find the mid point on the curve by arch length.
double tAtMidPoint = cubicBezier.archMidPoint();           // 0.70718
bezier::Point midPoint = cubicBezier.valueAt(tAtMidPoint); // (183.837, 168.768)
```
