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

    class ControlPoint
    {
    public:
        ControlPoint()
            : x(0)
            , y(0)
            , z(0)
        {}

        ControlPoint(float x, float y, float z)
            : x(x)
            , y(y)
            , z(z)
        {}

        ControlPoint(const ControlPoint& other)
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

        void move(float dx, float dy, float dz)
        {
            x += dx;
            y += dy;
            z += dz;
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
        {}

        Bezier(const std::vector<ControlPoint> controlPoints)
        {
            for (size_t i = 0; i < controlPoints.size(); i++)
                mControlPoints[i] = ControlPoint(controlPoints[i]);
        }

        Bezier(const Bezier<N>& other)
        {
            for (size_t i = 0; i < other.size(); i++)
                mControlPoints[i] = ControlPoint(other[i]);
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

    public:
        ControlPoint& operator [](size_t pos)
        {
            assert(pos < size());
            return mControlPoints[pos];
        }

    public:
        static const BinomialCoefficients<N> binomialCoefficients;

    private:
        ControlPoint mControlPoints[N+1];
    };

    template<size_t N>
    const BinomialCoefficients<N> Bezier<N>::binomialCoefficients = BinomialCoefficients<N>();

} // namespace Bezier
