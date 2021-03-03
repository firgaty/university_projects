#ifndef INCLUDE_VIEW_CLI_DISPLAYBLANKCLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYBLANKCLI_HPP_

#include "View/CLI/DisplayCLI.hpp"

class DisplayBlankCLI : public virtual DisplayCLI
{
private:
    void _gen_string_array()
    {
        _string_array.clear();
        _string_array.reserve(height());
        for (int i = 0; i < height(); i++)
            _string_array.push_back(std::u32string(width(), ' '));
    }

public:
    DisplayBlankCLI(Dimensions d)
    {
        _dimensions   = d;
        _string_array = StringArray();
        _gen_string_array();
    }
    ~DisplayBlankCLI() {}

    // void display() const;
    void gen_string_array() {}

    void dimensions(Dimensions d)
    {
        if (d != _dimensions) {
            _dimensions = d;
            _gen_string_array();
        }
    }
};

using BlankCLI = DisplayBlankCLI;

#endif // !INCLUDE_VIEW_CLI_DISPLAYBLANKCLI_HPP_