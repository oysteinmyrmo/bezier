#pragma once
#include <assert.h>
#include <math.h>
#include <vector>

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
            , z(0)
        {}

        Point(float x, float y, float z)
            : x(x)
            , y(y)
            , z(z)
        {}

        Point(const Point& other)
            : x(other.x)
            , y(other.y)
            , z(other.z)
        {}

        void set(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        void set(const Point& other)
        {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
        }

        void move(float dx, float dy, float dz)
        {
            x += dx;
            y += dy;
            z += dz;
        }

        double length() const
        {
            return sqrt(x*x + y*y + z*z);
        }

        void normalize()
        {
            double len = length();
            x /= len;
            y /= len;
            z /= len;
        }

        float operator[](size_t pos) const
        {
            assert(pos <= 2);
            switch (pos)
            {
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
                default:
                    return 0;
            }
        }

        float& operator[](size_t pos)
        {
            assert(pos <= 2);
            switch (pos)
            {
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
                default:
                    return x; // TODO: Better handling/printing
            }
        }

        Point operator+(const Point& other) const
        {
            return Point(x + other.x, y + other.y, z + other.z);
        }

        Point operator-(const Point& other) const
        {
            return Point(x - other.x, y - other.y, z - other.z);
        }

        Point operator*(double scale) const
        {
            return Point(x * scale, y * scale, z * scale);
        }

        Point operator/(double scale) const
        {
            return Point(x / scale, y / scale, z / scale);
        }

        float x;
        float y;
        float z;
    };

    template <size_t N>
    class Bezier
    {
    public:
        Bezier()
        {
            for (size_t i = 0; i < N+1; i++)
                mControlPoints[i].set(0, 0, 0);
        }

        Bezier(const std::vector<Point> controlPoints)
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
        Point valueAt(float t) const
        {
            Point p;
            for (size_t i = 0; i < 3; i++)
            {
                double sum = 0;
                for (size_t n = 0; n < N+1; n++)
                {
                    sum += binomialCoefficients[n] * polynomialCoefficients[n].valueAt(t) * mControlPoints[n][i];
                }
                p[i] = sum;
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
            p.set(-tangent.y, tangent.x, tangent.z);
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
