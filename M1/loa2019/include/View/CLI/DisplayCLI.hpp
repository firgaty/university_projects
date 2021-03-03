#ifndef INCLUDE_VIEW_CLI_DISPLAYCLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYCLI_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "Model/Color.hpp"
#include "Util/Convert.hpp"
#include "Util/Dimensional.hpp"
#include "Util/Point2D.hpp"
#include "View/Display.hpp"

using StringArray = std::vector<std::u32string>;

enum class DisplayState { FETCHED, GENERATED };

class DisplayCLI : public virtual Display, public virtual Dimensional
{
protected:
    StringArray _string_array;
    DisplayState _state;

    bool repaint_line(const size_t &line,
                      const size_t &begin,
                      const std::u32string &paint);

    void set_state_fetched();
    void set_state_generated();

public:
    DisplayCLI() : _state(DisplayState::FETCHED) {}
    virtual void display();
    virtual void gen_string_array() = 0;
    const StringArray &get_string_array();
    char char_from_color(const Color &) const;
    const Dimensions &dimensions() { return _dimensions; }
    virtual void dimensions(Dimensions d) { _dimensions = d; }

    bool repaint(const Point2D_u &origin, DisplayCLI &paint);
    bool repaint(DisplayCLI &paint) { return repaint(Point2D_u(0, 0), paint); }
};

#endif // INCLUDE_VIEW_CLI_DISPLAYCLI_HPP_