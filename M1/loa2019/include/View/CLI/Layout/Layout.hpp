#ifndef INCLUDE_VIEW_CLI_LAYOUT_LAYOUT_HPP_
#define INCLUDE_VIEW_CLI_LAYOUT_LAYOUT_HPP_

#include <vector>

#include "View/CLI/DisplayBlankCLI.hpp"
#include "View/CLI/DisplayCLI.hpp"

using DisplayVector = std::vector<DisplayCLI *>;

class Layout : public virtual DisplayCLI
{
protected:
    DisplayVector _elements;
    bool _visible_separator;
    size_t _gap;

    virtual void _set_dimensions() = 0;

public:
    Layout()
    {
        _string_array = StringArray();
        _elements     = DisplayVector();
        _elements.reserve(8);
        _dimensions        = Dimensions(0, 0);
        _visible_separator = false;
        _gap               = 1;
    }
    virtual ~Layout()
    {
        for (auto e : _elements)
            delete e;
    }

    void add_element(DisplayCLI *e)
    {
        set_state_fetched();
        _elements.push_back(e);
        _set_dimensions();
    }
    void remove_element(const size_t &index, bool delete_element = false)
    {
        if (_elements.size() > index) {
            set_state_fetched();
            if (delete_element)
                delete _elements.at(index);
            _elements.erase(_elements.cbegin() + index);
            _set_dimensions();
        }
    }
    DisplayCLI *get_element(const size_t &index)
    {
        if (_elements.size() > index)
            return _elements.at(index);
        return nullptr;
    }
    void set_visible_separator(bool visible)
    {
        _state             = DisplayState::FETCHED;
        _visible_separator = visible;
    }
    void set_gap(const size_t &gap)
    {
        set_state_fetched();
        _gap = gap;
    }
    void clear(bool delete_elements = true)
    {
        if (delete_elements)
            for (auto e : _elements)
                delete e;
        _elements.clear();
    }
    size_t size() { return _elements.size(); }
};

#endif // !INCLUDE_VIEW_CLI_LAYOUT_LAYOUT_HPP_