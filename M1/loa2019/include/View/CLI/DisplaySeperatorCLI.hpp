#ifndef INCLUDE_VIEW_CLI_DISPLAYSEPARATORCLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYSEPARATORCLI_HPP_

#include "View/CLI/DisplayCLI.hpp"

class DisplaySeparatorCLI : public virtual DisplayCLI
{
public:
    DisplaySeparatorCLI()  = default;
    virtual ~DisplaySeparatorCLI() {}
    virtual void set_decoration(const char& decoration) = 0;
    void set_dimensions() = delete;
};

class DisplayVSeparatorCLI : public virtual DisplaySeparatorCLI
{
public:
    DisplayVSeparatorCLI(const size_t &size, const char32_t decoration = L'|')
    {
        _dimensions   = Dimensions(size, 1);
        _string_array = StringArray();
        _string_array.reserve(size);
        set_decoration(decoration);
    }
    ~DisplayVSeparatorCLI() {}
    void gen_string_array() {}

    void set_decoration(const char& decoration) {
        _string_array.clear();
        for (int i = 0; i < height(); i++) {
            _string_array.push_back(std::u32string(1, decoration));
        }
    }
};

class DisplayHSeparatorCLI : public virtual DisplaySeparatorCLI
{
public:
    DisplayHSeparatorCLI(const size_t &size, const char32_t decoration = L'-')
    {
        _dimensions   = Dimensions(1, size);
        _string_array = StringArray();
        _string_array.reserve(1);
        set_decoration(decoration);
    }
    ~DisplayHSeparatorCLI() {}
    void gen_string_array() {}
    void set_decoration(const char& decoration) {
        _string_array.clear();
        _string_array.push_back(std::u32string(width(), decoration));
    }
};

using VSeparatorCLI = DisplayVSeparatorCLI;
using HSeparatorCLI = DisplayHSeparatorCLI;

#endif // !INCLUDE_VIEW_CLI_DISPLAYSEPARATORCLI_HPP_