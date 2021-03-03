#ifndef INCLUDE_VIEW_CLI_DISPLAYGROUPCLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYGROUPCLI_HPP_

#include "View/CLI/DisplayBoxCLI.hpp"
#include "View/CLI/DisplayLabelCLI.hpp"

class DisplayGroupCLI : public DisplayBoxCLI
{
protected:
    DisplayLabelCLI *_title_label;

public:
    DisplayGroupCLI(const std::string &title, DisplayCLI *element = nullptr)
        : DisplayBoxCLI(2, title.size() + 4)
    {
        _title_label = new LabelCLI("Group");
        set_title(title);
        set_element(element);
    }
    ~DisplayGroupCLI() { delete _title_label; }

    void set_title(const std::string &title)
    {
        set_state_fetched();
        _title_label->set_label(title);
        _title_label->gen_string_array();
        update_dimensions();
    }
    void set_dimensions(const Dimensions d)
    {
        BoxCLI::set_dimensions(d);

        // TODO: Multiple line title.
        repaint(Point2D_u(0, 2), *_title_label);
    }

    void update_dimensions()
    {
        Dimensions d(2, 2);

        if ((_element)) {
            _element->gen_string_array();
            d += Dimensions(_element->height(), 0);
            if (_element->width() > _title_label->width() + 2)
                d += Dimensions(0, _element->width());
            else
                d += Dimensions(0, _title_label->width() + 2);
        } else
            d += Dimensions(0, _title_label->width() + 2);

        set_dimensions(d);
    }

    void gen_string_array()
    {
        if (_state == DisplayState::GENERATED)
            return;
        _element->gen_string_array();
        BlankCLI blank(_dimensions - Point2D_u(2, 2));
        repaint(Point2D_u(1, 1), blank);
        set_dimensions(_element->dimensions() + Dimensions(2, 2));
        repaint(Point2D_u(1, 1), *_element);
    }
};

using GroupCLI = DisplayGroupCLI;

#endif // !INCLUDE_VIEW_CLI_DISPLAYGROUPCLI_HPP_