#ifndef INCLUDE_UTIL_POINT2D_HPP__
#define INCLUDE_UTIL_POINT2D_HPP__

#include <cassert>
#include <cmath>
#include <vector>

// TODO: Add restriction with `std::enable_if`
//       to int, flaot, double and usigned int

/**
 * @brief Template for basic 2D points
 *
 * @tparam T int, float, double or unsigned int
 */
template <typename T>
class Point2DTemplate
{
public:
    T _x, _y;

    Point2DTemplate();
    Point2DTemplate(T x, T y);
    Point2DTemplate(const Point2DTemplate<T> &p);
    Point2DTemplate(const std::vector<T> vec);

    /**
     * @brief Conversion constructor.
     *
     * @tparam U
     * @param other
     */
    template <typename U>
    Point2DTemplate(const Point2DTemplate<U> &other)
    {
        _x = other._x;
        _y = other._y;
    }

    ~Point2DTemplate();

    const T &x() const; // legacy
    const T &y() const; // legacy

    void x(T); // legacy
    void y(T); // legacy

    const double euclidian_distance(const Point2DTemplate<T> &b) const;
    static const double euclidian_distance(const Point2DTemplate<T> &a,
                                           const Point2DTemplate<T> &b)
    {
        return a.euclidian_distance(b);
    }
    const T diagonal_distance(const Point2DTemplate<T> &b) const;
    static const T diagonal_distance(const Point2DTemplate<T> &a,
                                     const Point2DTemplate<T> &b)
    {
        return a.diagonal_distance(b);
    }
    const T min_axis_distance(const Point2DTemplate<T> &b) const;
    static const T min_axis_distance(const Point2DTemplate<T> &a,
                                     const Point2DTemplate<T> &b)
    {
        return a.min_axis_distance(b);
    }
    const T manhattan_distance(const Point2DTemplate<T> &b) const;
    static const T manhattan_distance(const Point2DTemplate<T> &a,
                                      const Point2DTemplate<T> &b)
    {
        return a.manhattan_distance(b);
    }
};

template <typename T>
inline bool operator==(const Point2DTemplate<T> &a, const Point2DTemplate<T> &b)
{
    return a.x() == b.x() && a.y() == b.y();
}
template <typename T>
inline bool operator!=(const Point2DTemplate<T> &a, const Point2DTemplate<T> &b)
{
    return !(a == b);
}

template <typename T>
inline Point2DTemplate<T> operator+(const Point2DTemplate<T> &a,
                                    const Point2DTemplate<T> &b)
{
    return Point2DTemplate<T>(a.x() + b.x(), a.y() + b.y());
}

template <typename T>
inline Point2DTemplate<T> operator-(const Point2DTemplate<T> &a,
                                    const Point2DTemplate<T> &b)
{
    return Point2DTemplate<T>(a.x() - b.x(), a.y() - b.y());
}
template <typename T>
inline Point2DTemplate<T> operator*(const Point2DTemplate<T> &a,
                                    const Point2DTemplate<T> &b)
{
    return Point2DTemplate<T>(a.x() * b.x(), a.y() * b.y());
}

template <typename T>
inline void operator+=(Point2DTemplate<T> &a, const Point2DTemplate<T> &b)
{
    a = a + b;
}
template <typename T>
inline void operator-=(Point2DTemplate<T> &a, const Point2DTemplate<T> &b)
{
    a = a - b;
}
template <typename T>
inline void operator*=(Point2DTemplate<T> &a, const Point2DTemplate<T> &b)
{
    a = a * b;
}

#include <ostream>
// TODO rewrite for save.
template <typename T>
std::ostream &operator<<(std::ostream &os, const Point2DTemplate<T> &a)
{
    os << a.x() << " " << a.y();
    return os;
}

template <typename T>
Point2DTemplate<T>::Point2DTemplate() : Point2DTemplate<T>(0, 0)
{
}

template <typename T>
Point2DTemplate<T>::Point2DTemplate(T x, T y)
{
    _x = x;
    _y = y;
}

template <typename T>
Point2DTemplate<T>::Point2DTemplate(const Point2DTemplate<T> &p)
{
    _x = p.x();
    _y = p.y();
}

template <typename T>
Point2DTemplate<T>::Point2DTemplate(const std::vector<T> vec)
{
    assert(vec.size() == 2);
    _x = vec[0];
    _y = vec[1];
}

template <typename T>
Point2DTemplate<T>::~Point2DTemplate()
{
}

template <typename T>
const T &Point2DTemplate<T>::x() const
{
    return _x;
}
template <typename T>
const T &Point2DTemplate<T>::y() const
{
    return _y;
}

template <typename T>
void Point2DTemplate<T>::x(T x)
{
    _x = x;
}
template <typename T>
void Point2DTemplate<T>::y(T y)
{
    _y = y;
}

template <typename T>
const double
Point2DTemplate<T>::euclidian_distance(const Point2DTemplate<T> &b) const
{
    Point2DTemplate<double> da(*this), db(b);
    return std::sqrt(std::pow((da._x - db._x), 2)
                     + std::pow((da._y - db._y), 2));
}

template <typename T>
const T Point2DTemplate<T>::diagonal_distance(const Point2DTemplate<T> &b) const
{
    T x = std::abs(_x - b._x);
    T y = std::abs(_y - b._y);
    return std::max(x, y);
}

template <typename T>
const T Point2DTemplate<T>::min_axis_distance(const Point2DTemplate<T> &b) const
{
    T x = std::abs(_x - b._x);
    T y = std::abs(_y - b._y);
    return std::min(x, y);
}

template <typename T>
const T
Point2DTemplate<T>::manhattan_distance(const Point2DTemplate<T> &b) const
{
    T x = std::abs(_x - b._x);
    T y = std::abs(_y - b._y);
    return x + y;
}

using Point2D_i = Point2DTemplate<int>;
using Point2D_f = Point2DTemplate<float>;
using Point2D_d = Point2DTemplate<double>;
using Point2D_u = Point2DTemplate<unsigned long>;
using Point2D   = Point2D_i;

#endif // INCLUDE_UTIL_POINT2D_HPP__