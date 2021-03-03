#ifndef INCLUDE_VIEW_CLI_DISPLAYLINKEDITOR_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYLINKEDITOR_HPP_

#include "Model/Creator/LinkEditor.hpp"
#include "View/CLI/DisplayChoiceSelectCLI.hpp"
#include "View/CLI/DisplayGroupCLI.hpp"
#include "View/CLI/DisplayLevelCLI.hpp"
#include "View/CLI/DisplayNumberSelectorCLI.hpp"
#include "View/CLI/Layout/HLayout.hpp"
#include "View/CLI/Layout/VLayout.hpp"

class DisplayLinkEditorCLI : public DisplayContainerCLI
{
private:
    LinkEditor *_editor;
    DisplayChoiceSelectCLI *_menu;
    DisplayLevelCLI *_level;
    YesNoCLI *_yes_no;
    GroupCLI *_group;
    Layout *_layout;
    LabelCLI *_point_label;

    void cleanup()
    {
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

        _menu        = nullptr;
        _level       = nullptr;
        _yes_no      = nullptr;
        _group       = nullptr;
        _layout      = nullptr;
        _point_label = nullptr;
    }

public:
    DisplayLinkEditorCLI()
    {
        _editor      = nullptr;
        _menu        = nullptr;
        _level       = nullptr;
        _yes_no      = nullptr;
        _group       = nullptr;
        _layout      = nullptr;
        _point_label = nullptr;
    }
    DisplayLinkEditorCLI(LinkEditor *editor) : DisplayLinkEditorCLI()
    {
        set_link_editor(editor);
    }

    ~DisplayLinkEditorCLI()
    {
        switch (_editor->get_ac_state()) {
            case ACState::EXIT_YES_NO: delete _layout; break;
            case ACState::CATCH: delete _yes_no; break;
        }
    }

    void set_link_editor(LinkEditor *editor)
    {
        cleanup();
        VLayout *sec_layout = new VLayout();
        _editor             = editor;
        _menu               = new DisplayChoiceSelectCLI(editor->get_options());
        _yes_no             = new YesNoCLI(editor->get_exit_yes_no());
        _level              = new DisplayLevelCLI();
        _layout             = new HLayout();
        _point_label        = new LabelCLI("N/A");
        _layout->add_element(new GroupCLI("Level", _level));
        _layout->add_element(sec_layout);
        sec_layout->add_element(new GroupCLI("Options", _menu));
        _menu->set_labels({"1: Add Link", "2: Remove Link"});
        sec_layout->add_element(new GroupCLI("Diamond Coord", _point_label));
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
                if (_editor->get_state())
                    _point_label->set_label(
                        std::to_string(_editor->get_point().x()) + ":"
                        + std::to_string(_editor->get_point().y()));
                break;
        }
        _element->gen_string_array();
        _string_array = _element->get_string_array();
    }
};

#endif // !INCLUDE_VIEW_CLI_DISPLAYLINKEDITOR_HPP_