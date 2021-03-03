#ifndef INCLUDE_VIEW_CLI_DISPLAYLEVELLINKEDITOR_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYLEVELLINKEDITOR_HPP_

#include "Model/Creator/LevelLinkEditor.hpp"
#include "View/CLI/DisplayChoiceSelectCLI.hpp"
#include "View/CLI/DisplayGroupCLI.hpp"
#include "View/CLI/DisplayLevelCLI.hpp"
#include "View/CLI/DisplayNumberSelectorCLI.hpp"
#include "View/CLI/Layout/HLayout.hpp"
#include "View/CLI/Layout/VLayout.hpp"

class DisplayLevelLinkEditorCLI : public DisplayContainerCLI
{
private:
    LevelLinkEditor *_editor;
    DisplayChoiceSelectCLI *_menu;
    NumberBoxCLI *_selector;
    DisplayLevelCLI *_level;
    YesNoCLI *_yes_no;
    GroupCLI *_group;
    Layout *_layout;
    LabelCLI *_point_label, *_id_label, *_inst_label;

    void cleanup()
    {
        if (_editor)
            delete _editor;
        if (_menu)
            delete _menu;
        if (_level)
            delete _level;
        if (_yes_no)
            delete _yes_no;
        if (_group)
            delete _group;
        if (_layout)
            delete _layout;
        if (_point_label)
            delete _point_label;
        if (_selector)
            delete _selector;
        if (_id_label)
            delete _id_label;
        if (_inst_label)
            delete _inst_label;

        _editor      = nullptr;
        _menu        = nullptr;
        _level       = nullptr;
        _yes_no      = nullptr;
        _group       = nullptr;
        _layout      = nullptr;
        _point_label = nullptr;
        _selector    = nullptr;
        _id_label    = nullptr;
        _inst_label  = nullptr;
    }

public:
    DisplayLevelLinkEditorCLI()
    {
        _editor      = nullptr;
        _menu        = nullptr;
        _level       = nullptr;
        _yes_no      = nullptr;
        _group       = nullptr;
        _layout      = nullptr;
        _point_label = nullptr;
        _selector    = nullptr;
        _id_label    = nullptr;
        _inst_label  = nullptr;
    }
    DisplayLevelLinkEditorCLI(LevelLinkEditor *editor)
        : DisplayLevelLinkEditorCLI()
    {
        set_level_link_editor(editor);
    }

    ~DisplayLevelLinkEditorCLI() { cleanup(); }

    void set_level_link_editor(LevelLinkEditor *editor)
    {
        cleanup();
        VLayout *sec_layout   = new VLayout();
        VLayout *label_layout = new VLayout();
        _editor               = editor;
        _selector = new NumberBoxCLI(_editor->get_number_selector()->get(), 8);
        GroupCLI *selector_group = new GroupCLI("Level ID", _selector);
        // _menu               = new
        // DisplayChoiceSelectCLI(editor->get_options());
        _yes_no      = new YesNoCLI(editor->get_exit_yes_no());
        _level       = new DisplayLevelCLI();
        _layout      = new HLayout();
        _point_label = new LabelCLI("N/A");
        _id_label    = new LabelCLI("N/A");
        _inst_label  = new LabelCLI("Instruction");
        label_layout->set_gap(0);
        label_layout->add_element(_id_label);
        label_layout->add_element(_point_label);
        _layout->add_element(new GroupCLI("Select", _selector));
        _layout->add_element(new GroupCLI("Level", _level));
        _layout->add_element(sec_layout);
        // sec_layout->add_element(new GroupCLI("Options", _menu));
        // _menu->set_labels({"1: Add Link", "2: Remove Link"});
        sec_layout->add_element(new GroupCLI("From Level", label_layout));
        sec_layout->add_element(_inst_label);
        _group = new GroupCLI("LevelEditor", _layout);
        set_element(_group);
    }
    void gen_string_array()
    {
        switch (_editor->get_ac_state()) {
            case ACState::EXIT_YES_NO:
                _group->set_title("Continue ?");
                _group->set_element(_yes_no);
                break;
            case ACState::CATCH:
                _level->set_level(_editor->get_level());
                _group->set_title("Link Editor");
                _group->set_element(_layout);
                _selector->set_value(_editor->get_number_selector()->get());
                if (_editor->get_select()) {
                    if (_editor->get_state())
                        _inst_label->set_label("Level Select TO");
                    else
                        _inst_label->set_label("Level Select FROM");
                }
                if (_editor->get_state()) {
                    _point_label->set_label(
                        std::to_string(_editor->get_point().x()) + ":"
                        + std::to_string(_editor->get_point().y()));
                    _id_label->set_label(std::to_string(_editor->get_id()));
                    if (!_editor->get_select())
                        _inst_label->set_label("Square Select");
                } else {
                    if (!_editor->get_select())
                        _inst_label->set_label("Door Select");
                }
                break;
        }
        _element->gen_string_array();
        _string_array = _element->get_string_array();
    }
};

#endif // !INCLUDE_VIEW_CLI_DISPLAYLINKEDITOR_HPP_