#ifndef INCLUDE_VIEW_CLI_DISPLAYCONTAINERCLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYCONTAINERCLI_HPP_

#include "View/CLI/DisplayCLI.hpp"

class DisplayContainerCLI : public DisplayCLI
{
protected:
    DisplayCLI *_element = nullptr;
    bool _element_is_set;

public:
    DisplayContainerCLI() : Dimensional(), _element_is_set(false) {}
    DisplayContainerCLI(DisplayCLI *element) : DisplayContainerCLI()
    {
        set_element(element);
    }
    ~DisplayContainerCLI()
    {
        if (_element_is_set)
            delete _element;
    }
    virtual void set_element(DisplayCLI *element)
    {
        set_state_fetched();
        _element = element;
        if (_element == nullptr) {
            _element_is_set = false;
            dimensions({0, 0});
        } else {
            _element_is_set = true;
            _element->gen_string_array();
            dimensions(_element->dimensions());
        }
    }
    virtual void gen_string_array() = 0;
    DisplayCLI *get_element() { return _element; }
    const void unset_element()
    {
        set_element(nullptr);
        _element_is_set = false;
    }
};

#endif // !INCLUDE_VIEW_CLI_DISPLAYCONTAINERCLI_HPP_