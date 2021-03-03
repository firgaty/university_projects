#ifndef INCLUDE_VIEW_CLI_DISPLAYLEVELEDITOR_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYLEVELEDITOR_HPP_

#include "Model/Creator/LevelEditor.hpp"
#include "View/CLI/DisplayChoiceSelectCLI.hpp"
#include "View/CLI/DisplayGroupCLI.hpp"
#include "View/CLI/DisplayLevelCLI.hpp"
#include "View/CLI/DisplayNumberSelectorCLI.hpp"
#include "View/CLI/Layout/HLayout.hpp"
#include "View/CLI/Layout/VLayout.hpp"

class DisplayLevelEditorCLI : public DisplayContainerCLI
{
private:
    LevelEditor *_editor;
    DisplayChoiceSelectCLI *_menu;
    DisplayLevelCLI *_level;
    YesNoCLI *_yes_no;
    GroupCLI *_group;
    Layout *_layout;

    void cleanup()
    {
        if ((_menu))
            delete _menu;
        if ((_level))
            delete _level;
        if ((_yes_no))
            delete _yes_no;
        if ((_group))
            delete _group;
        if ((_layout))
            delete _layout;

        _menu   = nullptr;
        _level  = nullptr;
        _yes_no = nullptr;
        _group  = nullptr;
        _layout = nullptr;
    }

public:
    DisplayLevelEditorCLI()
    {
        _editor = nullptr;
        _menu   = nullptr;
        _level  = nullptr;
        _yes_no = nullptr;
        _group  = nullptr;
        _layout = nullptr;
    }
    DisplayLevelEditorCLI(LevelEditor *editor) : DisplayLevelEditorCLI()
    {
        set_level_editor(editor);
    }

    ~DisplayLevelEditorCLI()
    {
        if ((_editor))
            switch (_editor->get_ac_state()) {
                case ACState::EXIT_YES_NO: delete _layout; break;
                case ACState::CATCH: delete _yes_no; break;
            }
    }

    void set_level_editor(LevelEditor *editor)
    {
        if (_editor == editor)
            return;

        cleanup();
        _editor = editor;
        _menu   = new DisplayChoiceSelectCLI(editor->options());
        _yes_no = new YesNoCLI(editor->get_exit_yes_no());
        _level  = new DisplayLevelCLI();
        _layout = new HLayout();
        _layout->add_element(new GroupCLI("Level", _level));
        _layout->add_element(new GroupCLI("Options", _menu));
        _menu->set_labels({"1: Def Monster",
                           "2: Diag Monster",
                           "3: Cross Monster",
                           "4: Diamond",
                           "5: Charger",
                           "6: Charger Rnd",
                           "7: Charger Rnd Safe",
                           "8: Player",
                           "9: Remove"});
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
                _level->set_level(_editor->level());
                _group->set_title("Level Editor");
                _group->set_element(_layout);
                break;
        }
        _element->gen_string_array();
        _string_array = _element->get_string_array();
    }
};

#endif // !INCLUDE_VIEW_CLI_DISPLAYBOARDCREATOR_HPP_