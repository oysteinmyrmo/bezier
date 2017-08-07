#pragma once
#include <assert.h>
#include <math.h>
#include <vector>

// Cross platform define for printing size_t variables
#ifdef __WIN32__
#define BEZIER_SIZE_T_FORMAT "%ld"
#else
#define BEZIER_SIZE_T_FORMAT "%zd"
#endif

#define BEZIER_FUZZY_EPSILON 0.001
#define BEZIER_DEFAULT_INTERVALS 10
#define BEZIER_DEFAULT_MAX_ITERATIONS 15

namespace Bezier
{
    namespace Math
    {
        inline double faculty(size_t n)
        {
            double d = 1.0;
            if (n == 0 || n == 1)
                return d;
            for (size_t i = 2; i <= n; i++)
                d *= (double) i;
            return d;
        }

        // Note: Using faculty function seems to be way faster than the recursive one
        // given at https://en.wikipedia.org/wiki/Binomial_coefficient
        inline double binomial(size_t n, size_t k)
        {
            assert(k <= n);
            return faculty(n) / (faculty(k) * faculty(n - k));
        }

        inline bool isWithinZeroAndOne(float x)
        {
            return x >= -BEZIER_FUZZY_EPSILON && x <= (1.0 + BEZIER_FUZZY_EPSILON);
        }
    }

    template<size_t N>
    class BinomialCoefficients
    {
    public:
        BinomialCoefficients()
        {
            size_t center = N / 2;
            size_t k = 0;

            while (k <= center)
            {
                mCoefficients[k] = Math::binomial(N, k);
                k++;
            }

            // Utilize the symmetrical nature of the binomial coefficients.
            while (k <= N)
            {
                mCoefficients[k] = mCoefficients[N - k];
                k++;
            }
        }

        static constexpr size_t size()
        {
            return N + 1;
        }

        const size_t operator [](size_t idx) const
        {
            assert(idx < size());
            return mCoefficients[idx];
        }

    private:
        float mCoefficients[size()];
    };

    struct PolynomialPair
    {
        size_t t = 0;
        size_t one_minus_t = 0;

        double valueAt(float t) const
        {
            return pow(1 - t, one_minus_t) * pow(t, this->t);
        }
    };

    template<size_t N>
    class PolynomialCoefficients
    {
    public:
        PolynomialCoefficients()
        {
            for (size_t i = 0; i <= N; i++)
            {
                mPolynomialPairs[i].t = i;
                mPolynomialPairs[i].one_minus_t = N - i;
                assert(mPolynomialPairs[i].t + mPolynomialPairs[i].one_minus_t == N);
            }
        }

        double valueAt(size_t pos, float t) const
        {
            assert(pos < size());
            return mPolynomialPairs[pos].valueAt(t);
        }

        static constexpr size_t size()
        {
            return N + 1;
        }

        const PolynomialPair& operator [](size_t idx) const
        {
            assert(idx < size());
            return mPolynomialPairs[idx];
        }

    private:
        PolynomialPair mPolynomialPairs[size()];
    };

    class Point
    {
    public:
        Point()
            : x(0)
            , y(0)
        {}

        Point(float x, float y)
            : x(x)
            , y(y)
        {}

        Point(const Point& other)
            : x(other.x)
            , y(other.y)
        {}

        void set(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

        void set(const Point& other)
        {
            this->x = other.x;
            this->y = other.y;
        }

        void move(float dx, float dy)
        {
            x += dx;
            y += dy;
        }

        double length() const
        {
            return sqrt(x*x + y*y);
        }

        void normalize()
        {
            double len = length();
            x /= len;
            y /= len;
        }

        float operator[](size_t axis) const
        {
            assert(axis < Point::size);
            switch (axis)
            {
                case 0:
                    return x;
                case 1:
                    return y;
                default:
                    fprintf(stderr, "Erroneous axis: " BEZIER_SIZE_T_FORMAT ". Returning 0.\n", axis);
                    return 0;
            }
        }

        float& operator[](size_t axis)
        {
            assert(axis < Point::size);
            switch (axis)
            {
                case 0:
                    return x;
                case 1:
                    return y;
                default:
                    fprintf(stderr, "Erroneous axis: " BEZIER_SIZE_T_FORMAT ". Returning x.\n", axis);
                    return x;
            }
        }

        Point operator+(const Point& other) const
        {
            return Point(x + other.x, y + other.y);
        }

        Point operator-(const Point& other) const
        {
            return Point(x - other.x, y - other.y);
        }

        Point operator*(double scale) const
        {
            return Point(x * scale, y * scale);
        }

        Point operator/(double scale) const
        {
            return Point(x / scale, y / scale);
        }

        Point operator/(const Point& other) const
        {
            return Point(x / other.x, y / other.y);
        }

        bool fuzzyEquals(const Point& other) const
        {
            bool equals = true;
            for (size_t axis = 0; axis < Point::size; axis++)
            {
                if (fabs((*this)[axis] - other[axis]) >= BEZIER_FUZZY_EPSILON)
                {
                    equals = false;
                    break;
                }
            }
            return equals;
        }

        bool isWithinZeroAndOne() const
        {
            return Math::isWithinZeroAndOne(x) && Math::isWithinZeroAndOne(y);
        }

        float x;
        float y;
        static constexpr size_t size = 2;
    };

    struct ExtremeValue
    {
        ExtremeValue(float t, size_t axis)
            : t(t)
            , axis(axis)
        {}

        bool fuzzyEquals(const ExtremeValue& other) const
        {
            return axis == other.axis && fabs(t - other.t) < BEZIER_FUZZY_EPSILON;
        }

        const float t;
        const size_t axis;
    };

    class ExtremeValues
    {
    public:
        bool add(float t, size_t axis)
        {
            return add(ExtremeValue(t, axis));
        }

        bool add(const ExtremeValue& val)
        {
            assert(Math::isWithinZeroAndOne(val.t));
            for (auto const &v : values)
            {
                if (val.fuzzyEquals(v))
                    return false;
            }
            values.push_back(val);
            return true;
        }

        size_t size() const
        {
            return values.size();
        }

        ExtremeValue& operator[](size_t idx)
        {
            assert(idx < values.size());
            return values[idx];
        }

        ExtremeValue operator[](size_t idx) const
        {
            assert(idx < values.size());
            return values[idx];
        }

    private:
        std::vector<ExtremeValue> values;
    };

    struct ExtremePoint
    {
        ExtremePoint(float x, float y)
            : point(x, y)
        {}

        ExtremePoint(const Point& p)
            : point(p)
        {}

        ExtremePoint(const ExtremePoint& other)
            : point(other.point)
        {}

        Point point;
    };

    class ExtremePoints
    {
    public:
        bool add(float x, float y)
        {
            return add(ExtremePoint(x, y));
        }

        bool add(const Point& p)
        {
            return add(ExtremePoint(p));
        }

        bool add(const ExtremePoint& extremePoint)
        {
            for (auto const &ep : points)
            {
                if (extremePoint.point.fuzzyEquals(ep.point))
                    return false;
            }
            points.push_back(extremePoint);
            return true;
        }

        size_t size() const
        {
            return points.size();
        }

        ExtremePoint& operator[](size_t idx)
        {
            assert(idx < size());
            return points[idx];
        }

        ExtremePoint operator[](size_t idx) const
        {
            assert(idx < size());
            return points[idx];
        }

    private:
        std::vector<ExtremePoint> points;
    };

    template <size_t N>
    class Bezier
    {
    public:
        Bezier()
        {
            for (size_t i = 0; i < N+1; i++)
                mControlPoints[i].set(0, 0);
        }

        Bezier(const std::vector<Point>& controlPoints)
        {
            for (size_t i = 0; i < controlPoints.size(); i++)
                mControlPoints[i] = Point(controlPoints[i]);
        }

        Bezier(const Bezier<N>& other)
        {
            for (size_t i = 0; i < other.size(); i++)
                mControlPoints[i] = Point(other[i]);
        }

        // The order of the bezier curve.
        size_t order() const
        {
            return N;
        }

        // Number of control points.
        size_t size() const
        {
            return N + 1;
        }

        Bezier<N-1> derivative() const
        {
            assert(N > 0);

            // Note: derivative weights/control points are not actual control points.
            std::vector<Point> derivativeWeights(N);
            for (size_t i = 0; i < N; i++)
                derivativeWeights[i].set(Point((mControlPoints[i+1] - mControlPoints[i]) * N));

            return Bezier<N-1>(derivativeWeights);
        }

    public:
        double valueAt(float t, size_t axis) const
        {
            double sum = 0;
            for (size_t n = 0; n < N+1; n++)
            {
                sum += binomialCoefficients[n] * polynomialCoefficients[n].valueAt(t) * mControlPoints[n][axis];
            }
            return sum;
        }

        Point valueAt(float t) const
        {
            Point p;
            for (size_t i = 0; i < Point::size; i++)
            {
                p[i] = (float) valueAt(t, i);
            }
            return p;
        }

        Point tangentAt(float t, bool normalize = true) const
        {
            Point p;
            Bezier<N-1> derivative = this->derivative();
            p.set(derivative.valueAt(t));
            if (normalize)
                p.normalize();
            return p;
        }

        Point normalAt(float t, bool normalize = true) const
        {
            Point p;
            Point tangent = tangentAt(t, normalize);
            p.set(-tangent.y, tangent.x);
            return p;
        }

        ExtremeValues derivativeZero(size_t intervals = BEZIER_DEFAULT_INTERVALS,
                                     double epsilon = BEZIER_FUZZY_EPSILON,
                                     size_t maxIterations = BEZIER_DEFAULT_MAX_ITERATIONS) const
        {
            switch (N)
            {
                case 1:
                    return derivativeZero1();
                case 2:
                    return derivativeZero2();
                case 3:
//                    return derivativeZero3();
                    return newtonRhapson(intervals, epsilon, maxIterations);
                default:
                    return newtonRhapson(intervals, epsilon, maxIterations);
            }
        }

        ExtremePoints extremePoints() const
        {
            ExtremeValues xVals = derivativeZero();
            xVals.add(0.0f, 0);
            xVals.add(1.0f, 0);

            ExtremePoints xPoints;
            for (size_t i = 0; i < xVals.size(); i++)
                xPoints.add(ExtremePoint(valueAt(xVals[i].t)));

            return xPoints;
        }

    public:
        Point& operator [](size_t idx)
        {
            assert(idx < size());
            return mControlPoints[idx];
        }

        Point operator [](size_t idx) const
        {
            assert(idx < size());
            return mControlPoints[idx];
        }

    private:
        ExtremeValues derivativeZero1() const
        {
            assert(N == 1);
            return ExtremeValues();
        }

        ExtremeValues derivativeZero2() const
        {
            assert(N == 2);
            ExtremeValues xVals;
            Point roots = (mControlPoints[0] - mControlPoints[1]) / (mControlPoints[0] - mControlPoints[1] * 2 + mControlPoints[2]);
            if (Math::isWithinZeroAndOne(roots[0]))
                xVals.add(roots[0], 0);
            if (Math::isWithinZeroAndOne(roots[1]))
                xVals.add(roots[1], 1);
            return xVals;
        }

        ExtremeValues derivativeZero3() const
        {
            // Note: NOT IMPLMENTED YET
            assert(N == 3);
            return ExtremeValues();
        }

        ExtremeValues newtonRhapson(size_t intervals = BEZIER_DEFAULT_INTERVALS,
                                    double epsilon = BEZIER_FUZZY_EPSILON,
                                    size_t maxIterations = BEZIER_DEFAULT_MAX_ITERATIONS) const
        {
            assert(N >= 2);
            ExtremeValues xVals;
            const double dt = 1.0 / (double) intervals;
            const double absEpsilon = fabs(epsilon);
            const Bezier<N-1> db = derivative();
            const Bezier<N-2> ddb = db.derivative();

            for (size_t i = 0; i < Point::size; i++)
            {
                double t = 0;

                while(t <= 1.0)
                {
                    double zeroVal = t;
                    size_t current_iter = 0;

                    while (current_iter < maxIterations)
                    {
                        double dbVal = db.valueAt(zeroVal, i);
                        double ddbVal = ddb.valueAt(zeroVal, i);
                        double nextZeroVal = zeroVal - (dbVal / ddbVal);

                        if (fabs(nextZeroVal - zeroVal) < absEpsilon)
                        {
                            if (Math::isWithinZeroAndOne(nextZeroVal))
                            {
                                xVals.add(nextZeroVal, i);
                                break;
                            }
                        }

                        zeroVal = nextZeroVal;
                        current_iter++;
                    }

                    t += dt;
                }
            }

            return xVals;
        }

    public:
        static const BinomialCoefficients<N> binomialCoefficients;
        static const PolynomialCoefficients<N> polynomialCoefficients;

    private:
        Point mControlPoints[N+1];
    };

    template<size_t N>
    const BinomialCoefficients<N> Bezier<N>::binomialCoefficients = BinomialCoefficients<N>();

    template<size_t N>
    const PolynomialCoefficients<N> Bezier<N>::polynomialCoefficients = PolynomialCoefficients<N>();

} // namespace Bezier
