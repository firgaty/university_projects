#ifndef INCLUDE_VIEW_CLI_DISPLAYBOXCLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYBOXCLI_HPP_

#include "View/CLI/DisplayBlankCLI.hpp"
#include "View/CLI/DisplayCLI.hpp"
#include "View/CLI/DisplayContainerCLI.hpp"
#include "View/CLI/DisplaySeperatorCLI.hpp"

class DisplayBoxCLI : public virtual DisplayContainerCLI
{
protected:
    size_t _min_height, _min_width;

    void check_dimensions()
    {
        if (_dimensions.x() < _min_height)
            _dimensions.x(_min_height);
        if (_dimensions.y() < _min_width)
            _dimensions.y(_min_width);
    }

public:
    DisplayBoxCLI(const size_t &min_height, const size_t &min_width)
        : _min_height(min_height), _min_width(min_width)
    {
        _string_array = StringArray();
    }
    DisplayBoxCLI() : DisplayBoxCLI(2, 2) {}
    DisplayBoxCLI(DisplayCLI *element) : DisplayBoxCLI()
    {
        set_element(element);
    }
    ~DisplayBoxCLI() {}
    virtual void gen_string_array()
    {
        if (_state == DisplayState::GENERATED)
            return;

        _element->gen_string_array();
        if (_element->dimensions() != _dimensions - Dimensions(2, 2))
            set_dimensions(_element->dimensions() + Dimensions(2, 2));
        repaint(Point2D_u(1, 1), *_element);
    }

    virtual void set_dimensions(const Dimensions &d)
    {
        set_state_fetched();
        _dimensions = d;
        check_dimensions();

        _string_array.reserve(height());
        _string_array = BlankCLI(_dimensions).get_string_array();

        HSeparatorCLI hsep(width());
        VSeparatorCLI vsep(height());

        repaint(Point2D_u(0, 0), hsep);
        repaint(Point2D_u(0, width() - 1), vsep);
        repaint(Point2D_u(0, 0), vsep);
        repaint(Point2D_u(height() - 1, 0), hsep);
        _string_array[0][0]                      = '+';
        _string_array[0][width() - 1]            = '+';
        _string_array[height() - 1][0]           = '+';
        _string_array[height() - 1][width() - 1] = '+';
    }
    virtual void set_element(DisplayCLI *element)
    {
        if (element == _element)
            return;
        _state   = DisplayState::FETCHED;
        _element = element;
        update_dimensions();
    }
    virtual void update_dimensions()
    {
        _element->gen_string_array();
        set_dimensions(_element->dimensions()
                       + Dimensions(_min_height, _min_width));
    }
};

using BoxCLI = DisplayBoxCLI;

#endif // !INCLUDE_VIEW_CLI_DISPLAYBOXCLI_HPP_