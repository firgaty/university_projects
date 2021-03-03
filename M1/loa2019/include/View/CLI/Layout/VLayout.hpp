#ifndef INCLUDE_VIEW_CLI_LAYOUT_VLAYOUT_HPP_
#define INCLUDE_VIEW_CLI_LAYOUT_VLAYOUT_HPP_

#include "View/CLI/DisplaySeperatorCLI.hpp"
#include "View/CLI/Layout/Layout.hpp"

class VLayout : virtual public Layout
{
protected:
    void _set_dimensions()
    {
        _dimensions = Dimensions(0, 0);
        for (DisplayCLI *e : _elements) {
            _dimensions += Dimensions(e->height() + _gap, 0);
            if (width() < e->width())
                _dimensions = Dimensions(height(), e->width());
        }
        _dimensions -= Dimensions(_gap, 0);
        _string_array = BlankCLI(_dimensions).get_string_array();
    }

public:
    VLayout() : Layout() {}
    ~VLayout() {}

    void gen_string_array()
    {
        if(_state == DisplayState::GENERATED)
         return;

        for (auto e : _elements)
            e->gen_string_array();
        _set_dimensions();

        size_t l = 0;
        HSeparatorCLI sep(width());

        for (DisplayCLI *e : _elements) {
            repaint(Point2D_u(l, 0), *e);
            l += e->height();
            if (_visible_separator)
                for (int i = 0; i < _gap; i++)
                    repaint(Point2D_u(l + i, 0), sep);
            l += _gap;
        }
        set_state_generated();
    }
};

#endif // !INCLUDE_VIEW_CLI_LAYOUT_VLAYOUT_HPP_