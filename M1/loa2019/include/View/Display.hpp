#ifndef INCLUDE_VIEW_DISPLAY_HPP_
#define INCLUDE_VIEW_DISPLAY_HPP_

class Display
{
public:
    Display()              = default;
    virtual ~Display()     = default;
    virtual void display() = 0;
};

#endif // INCLUDE_VIEW_DISPLAY_HPP_
