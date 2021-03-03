#ifndef INCLUDE_MODEL_COLORED_HPP_
#define INCLUDE_MODEL_COLORED_HPP_

#include "Color.hpp"

class Colored
{
private:
    Color _color;

protected:
    Colored() { _color = Color::EMPTY; }
    explicit Colored(Color c) { _color = c; }

public:
    virtual const Color& color() const { return _color; }
    void set_color(Color c) { _color = c; }
    ~Colored() {}
};

#endif // INCLUDE_MODEL_COLORED_HPP_