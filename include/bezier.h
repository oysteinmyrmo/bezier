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

        const size_t size() const
        {
            return N + 1;
        }

        const size_t operator [](size_t pos) const
        {
            return mCoefficients[pos];
        }

    private:
        float mCoefficients[N+1];
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

        const size_t size() const
        {
            return N + 1;
        }

        const PolynomialPair& operator [](size_t pos) const
        {
            return mPolynomialPairs[pos];
        }

    private:
        PolynomialPair mPolynomialPairs[N+1];
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

        float x;
        float y;
        static constexpr size_t size = 2;
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
                derivativeWeights[i] = Point((mControlPoints[i+1] - mControlPoints[i]) * N);

            Bezier<N-1> bezier(derivativeWeights);
            return bezier;
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

    public:
        Point& operator [](size_t pos)
        {
            assert(pos < size());
            return mControlPoints[pos];
        }

        Point operator [](size_t pos) const
        {
            assert(pos < size());
            return mControlPoints[pos];
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
