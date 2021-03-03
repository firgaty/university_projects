#ifndef INCLUDE_UTIL_DIMENSIONAL_HPP_
#define INCLUDE_UTIL_DIMENSIONAL_HPP_

#include "Point2D.hpp"

using Dimensions = Point2D_u;
using Height     = unsigned int;
using Width      = unsigned int;

class Dimensional
{
protected:
    Dimensions _dimensions;

public:
    Dimensional() : _dimensions(Dimensions(0, 0)) {}
    Dimensional(const Dimensions &d) : _dimensions(Dimensions(d)) {}
    Dimensional(const Height &x, const Width &y) : _dimensions(Dimensions(x, y))
    {
    }
    Dimensional(const Dimensional &d) : _dimensions(d.dimensions()) {}

    virtual ~Dimensional() = 0;

    const Height x() const { return height(); } // legacy
    const Width y() const { return width(); }   // legacy
    const Height height() const { return _dimensions.x(); }
    const Width width() const { return _dimensions.y(); }
    const Dimensions &dimensions() const { return _dimensions; }

    void set_dimensions(const Dimensions &d) { _dimensions = d; }
    void set_dimensions(const Height &x, const Width &y)
    {
        _dimensions = Dimensions(x, y);
    }
    const bool contains(const std::size_t &x, const std::size_t &y) const
    {
        return x < _dimensions.x() && y < _dimensions.y();
    }
    const bool contains(const Point2D_u &p) const
    {
        return contains(p.x(), p.y());
    }
};

inline Dimensional::~Dimensional() {}

#endif // !INCLUDE_UTIL_DIMENSIONAL_HPP_