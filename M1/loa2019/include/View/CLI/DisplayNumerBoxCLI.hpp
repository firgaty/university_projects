#ifndef INCLUDE_VIEW_CLI_DISPLAYNUMBERBOXCLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYNUMBERBOXCLI_HPP_

#include "Util/Convert.hpp"
#include "View/CLI/DisplayCLI.hpp"

class DisplayNumberBoxCLI : public virtual DisplayCLI
{
private:
    int _value;
    size_t _min_width;

    int value_width()
    {
        int i        = abs(_value);
        size_t width = 0;
        do {
            width++;
        } while (i /= 10);
        if (_value < 0) // neg sign
            width++;
        return width;
    }

public:
    DisplayNumberBoxCLI(const int &value = 0, const size_t &min_width = 1)
        : _value(value), _min_width(0)
    {
        _string_array = StringArray();
        set_value(value, min_width);
    }

    void gen_string_array() {}

    void set_value(const int &value) { set_value(value, _min_width); }

    void set_value(const int &value, const size_t &min_width)
    {
        if (value == _value && min_width == _min_width)
            return;
        _value     = value;
        _min_width = min_width;
        int w      = value_width();
        int width  = w;
        if (width < _min_width)
            width = _min_width;
        dimensions(Dimensions(1, width));

        _string_array.clear();
        _string_array.push_back(Convert::to_utf32(""));

        for (int i = 0; i < width - w; i++) {
            _string_array[0].push_back(' ');
        }
        _string_array[0] += Convert::to_utf32(std::to_string(_value));
    }
};

using NumberBoxCLI = DisplayNumberBoxCLI;

#endif //! INCLUDE_VIEW_CLI_DISPLAYNUMBERBOXCLI_HPP_
