#ifndef INCLUDE_VIEW_CLI_DISPLAYLABELCLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYLABELCLI_HPP_

#include "Util/Convert.hpp"
#include "View/CLI/DisplayCLI.hpp"

class DisplayLabelCLI : public virtual DisplayCLI
{
private:
    std::u32string _string;

    const size_t count_lines()
    {
        size_t out = 1;
        for (char32_t c : _string) {
            if (c == '\n')
                out++;
        }
        return out;
    }

public:
    DisplayLabelCLI(const std::u32string s)
    {
        _string_array = StringArray();
        set_label(s);
    }

    DisplayLabelCLI(const std::string s) : DisplayLabelCLI(Convert::to_utf32(s))
    {
    }
    void gen_string_array(){};
    void set_label(const std::u32string s)
    {
        _string = s;
        _string_array.clear();
        size_t line_nb = count_lines();
        _string_array.reserve(line_nb);
        size_t len = s.size();

        // performance
        if (line_nb == 1) {
            _string_array.push_back(_string);
            _dimensions = Dimensions(1, s.size());
            return;
        }

        size_t cursor = 0, width = 0, nb = 0;
        for (int i = 0; i < len; i++) {
            if (_string[i] == L'\n') {
                _string_array.push_back(_string.substr(cursor, i - cursor));
                if (width < i - cursor)
                    width = i - cursor;
                cursor = i + 1;
            }
        }
        _string_array.push_back(_string.substr(cursor, len - cursor));
        if (width < len - cursor)
            width = len - cursor;
        _dimensions = Dimensions(line_nb, width);
    }
    void set_label(const std::string s) { set_label(Convert::to_utf32(s)); }
};

using LabelCLI = DisplayLabelCLI;

#endif // !INCLUDE_VIEW_CLI_DISPLAYLABELCLI_HPP_