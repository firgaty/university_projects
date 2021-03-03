#ifndef INCLUDE_VIEW_CLI_NUMBERSELECTORCLI_HPP_
#define INCLUDE_VIEW_CLI_NUMBERSELECTORCLI_HPP_

#include "Model/NumberSelector.hpp"
#include "View/CLI/DisplayChoiceSelectCLI.hpp"

class DisplayNumberSelectorCLI : public DisplayChoiceSelectCLI
{
protected:
    NumberSelector *_selector;

    virtual void setup()
    {
        _main_layout   = new VLayout();
        _text_layout   = new HLayout();
        _select_layout = new HLayout();
        _main_layout->add_element(_text_layout);
        _main_layout->add_element(_select_layout);
        _main_layout->set_gap(0);
        _select_layout->set_gap(1);
        _text_layout->set_gap(1);
        _element     = _main_layout;
        _with_prefix = false;
        _dimensions  = _element->dimensions();
    }

    void set_default_labels()
    {
        _text_layout->clear();
        std::vector<DigitSelector *> digits = _selector->digit_selectors();

        size_t counter = 0;
        bool pre       = false;
        for (size_t e : _selector->n_digits()) {
            if (pre)
                _text_layout->add_element(new LabelCLI(_prefix));

            for (int i = 0; i < e; i++)
                _text_layout->add_element(
                    new LabelCLI(std::to_string(digits[counter++]->get())));

            pre = true;
        }
    }

public:
    DisplayNumberSelectorCLI(NumberSelector *selector)
        : DisplayChoiceSelectCLI(selector, false, "x"), _selector(selector)
    {
        use_prefix(false);
        set_default_labels();
        set_option_style(OptionStyle::ARROW);
        setup();
    }

    virtual void gen_string_array()
    {
        if (_state == DisplayState::GENERATED)
            return;

        set_select();
        set_default_labels();
        _element->gen_string_array();
        _string_array = _element->get_string_array();

        _dimensions = _element->dimensions();
        set_state_generated();
    }

    virtual void set_select()
    {
        if (_state == DisplayState::GENERATED)
            return;

        _select_layout->clear();

        std::string s;
        switch (_option_style) {
            case OptionStyle::ARROW: s = "^"; break;
            case OptionStyle::STAR: s = "*"; break;
            case OptionStyle::PLUS: s = "+"; break;
        }
        int width   = 0;
        int counter = 0;
        for (size_t e : _selector->n_digits()) {

            for (int i = 0; i < e; i++) {
                if (counter == _selector->get())
                    goto for_exit_label;
                counter++;
                width += 2;
            }
            width += _prefix.length() + 1;
        }
    for_exit_label:

        if (width > 0)
            _select_layout->add_element(new BlankCLI(Dimensions(1, width - 1)));
        _select_layout->add_element(new LabelCLI(s));
    }
};

#endif