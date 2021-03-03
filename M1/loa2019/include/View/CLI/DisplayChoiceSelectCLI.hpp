#ifndef INCLUDE_VIEW_CLI_DISPLAYCHOICESELECTCLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYCHOICESELECTCLI_HPP_

#include "Model/ChoiceSelect.hpp"
#include "View/CLI/DisplayBlankCLI.hpp"
#include "View/CLI/DisplayContainerCLI.hpp"
#include "View/CLI/DisplayLabelCLI.hpp"
#include "View/CLI/Layout/HLayout.hpp"
#include "View/CLI/Layout/VLayout.hpp"

enum class OptionStyle { ARROW, STAR, PLUS };

class DisplayChoiceSelectCLI : public DisplayContainerCLI
{
protected:
    ChoiceSelect *_choice;
    OptionStyle _option_style;

    Layout *_main_layout;
    Layout *_text_layout;
    Layout *_select_layout;

    bool _with_prefix;
    std::string _prefix;

    const bool _vertical;

    std::vector<std::string> _labels;
    bool _labels_set;

    virtual void setup()
    {
        if (_vertical) {
            _main_layout   = new HLayout();
            _text_layout   = new VLayout();
            _select_layout = new VLayout();
            _main_layout->add_element(_select_layout);
            _main_layout->add_element(_text_layout);
            _text_layout->set_gap(0);
            _select_layout->set_gap(0);
        } else {
            _main_layout   = new VLayout();
            _text_layout   = new HLayout();
            _select_layout = new HLayout();
            _main_layout->add_element(_text_layout);
            _main_layout->add_element(_select_layout);
            _main_layout->set_gap(0);
        }

        _element = _main_layout;

        _with_prefix = false;
        _dimensions  = _element->dimensions();
    }

    void set_labels()
    {
        if (_choice->is_dynamic() || !_labels_set) {
            set_default_labels();
            return;
        }

        _text_layout->clear();

        for (auto e : _labels)
            _text_layout->add_element(new LabelCLI(e));
    }

    virtual void set_default_labels()
    {
        _text_layout->clear();
        for (int i(0); i < _choice->max(); i++)
            _text_layout->add_element(new LabelCLI(
                (_with_prefix ? _prefix + " " : "") + std::to_string(i)));
    }

    virtual void set_select()
    {
        if (_state == DisplayState::GENERATED)
            return;

        _select_layout->clear();

        if (_vertical) {
            int wide;
            std::string s;

            switch (_option_style) {
                case OptionStyle::ARROW:
                    wide = 2;
                    s    = "->";
                    break;
                case OptionStyle::STAR:
                    wide = 1;
                    s    = "*";
                    break;
                case OptionStyle::PLUS:
                    wide = 1;
                    s    = "+";
                    break;
            }

            if (_choice->get() > 0)
                _select_layout->add_element(
                    new BlankCLI(Dimensions(_choice->get(), wide)));

            _select_layout->add_element(new LabelCLI(s));

            // Not necessary
            if (_choice->max() - _choice->get() > 1)
                _select_layout->add_element(new BlankCLI(
                    Dimensions(_choice->max() - _choice->get() - 1, wide)));
        } else {
            std::string s;
            switch (_option_style) {
                case OptionStyle::ARROW: s = "^"; break;
                case OptionStyle::STAR: s = "*"; break;
                case OptionStyle::PLUS: s = "+"; break;
            }
            int width = 0;
            for (int i = 0; i < _choice->get(); i++) {
                width += _text_layout->get_element(i)->width() + 1;
            }
            if (width > 0)
                _select_layout->add_element(
                    new BlankCLI(Dimensions(1, width - 1)));
            _select_layout->add_element(new LabelCLI(s));
        }
    }

public:
    DisplayChoiceSelectCLI(ChoiceSelect *choice,
                           const bool &vertical      = true,
                           const std::string &prefix = "Option")
        : _prefix(prefix), _vertical(vertical)
    {
        _choice       = choice;
        _option_style = OptionStyle::ARROW;
        setup();
        set_default_labels();
        set_select();
        gen_string_array();
        set_state_fetched();
    }

    DisplayChoiceSelectCLI(ChoiceSelect *choice,
                           std::vector<std::string> &labels,
                           const bool &vertical = true)
        : _prefix("Option"), _vertical(vertical)
    {
        _choice       = choice;
        _option_style = OptionStyle::ARROW;

        setup();

        if (!set_labels(labels))
            set_default_labels();

        set_select();
        gen_string_array();
        set_state_fetched();
    }

    ~DisplayChoiceSelectCLI() = default;

    virtual void gen_string_array()
    {
        if (_state == DisplayState::GENERATED)
            return;

        set_select();
        if (_choice->is_dynamic())
            set_default_labels();
        _element->gen_string_array();
        _string_array = _element->get_string_array();

        _dimensions = _element->dimensions();
        set_state_generated();
    }

    bool set_labels(std::vector<std::string> labels)
    {
        if (labels.size() != _choice->max() || _choice->is_dynamic())
            return false;

        _labels     = labels;
        _labels_set = true;
        set_labels();

        set_state_fetched();
        return true;
    }

    void set_option_style(const OptionStyle &style)
    {
        _option_style = style;
        set_state_fetched();
    }
    void set_prefix(const std::string string)
    {
        _prefix = string;
        set_state_fetched();
    }
    void use_prefix(const bool &use)
    {
        _with_prefix = use;
        set_state_fetched();
    }
};

using ChoiceSelectCLI = DisplayChoiceSelectCLI;

class DisplayYesNoCLI : public DisplayChoiceSelectCLI
{
public:
    DisplayYesNoCLI(YesNo *yes_no, bool vertical = true)
        : DisplayChoiceSelectCLI(yes_no, vertical)
    {
        std::vector<std::string> vec;
        vec.push_back("No");
        vec.push_back("Yes");
        set_labels(vec);
    }
};

using YesNoCLI = DisplayYesNoCLI;

#endif // !INCLUDE_VIEW_CLI_DISPLAYCHOICESELECTCLI_HPP_