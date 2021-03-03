#ifndef INCLUDE_VIEW_CLI_LAYOUT_HLAYOUT_HPP_
#define INCLUDE_VIEW_CLI_LAYOUT_HLAYOUT_HPP_

#include "View/CLI/DisplaySeperatorCLI.hpp"
#include "View/CLI/Layout/Layout.hpp"

class HLayout : virtual public Layout
{
protected:
    void _set_dimensions()
    {
        _dimensions = Dimensions(0, 0);
        for (DisplayCLI *e : _elements) {
            _dimensions += Dimensions(0, e->width() + _gap);
            if (height() < e->height())
                _dimensions = Dimensions(e->height(), width());
        }
        _dimensions -= Dimensions(0, _gap);
        _string_array = BlankCLI(_dimensions).get_string_array();
    }

public:
    HLayout() : Layout() {}
    ~HLayout() {}

    void gen_string_array()
    {
        if (_state == DisplayState::GENERATED)
            return;

        for (auto e : _elements)
            e->gen_string_array();
        _set_dimensions();

        size_t l = 0;
        VSeparatorCLI sep(height());

        for (DisplayCLI *e : _elements) {
            repaint(Point2D_u(0, l), *e);
            l += e->width();
            if (_visible_separator)
                for (int i = 0; i < _gap; i++)
                    repaint(Point2D_u(0, l + i), sep);
            l += _gap;
        }
        set_state_generated();
    }
};

#endif // !INCLUDE_VIEW_CLI_LAYOUT_HLAYOUT_HPP_