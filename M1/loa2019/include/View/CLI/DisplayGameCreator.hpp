#ifndef INCLUDE_VIEW_CLI_GAMECREATORCLI_HPP_
#define INCLUDE_VIEW_CLI_GAMECREATORCLI_HPP_

#include "Model/Creator/GameCreator.hpp"
#include "View/CLI/DisplayBoardCreatorCLI.hpp"
#include "View/CLI/DisplayChoiceSelectCLI.hpp"
#include "View/CLI/DisplayContainerCLI.hpp"
#include "View/CLI/DisplayGroupCLI.hpp"
#include "View/CLI/DisplayLevelEditor.hpp"
#include "View/CLI/DisplayLevelLinkEditor.hpp"
#include "View/CLI/DisplayLinkEditor.hpp"

class DisplayGameCreatorCLI : public DisplayContainerCLI
{
private:
    GameCreator *_creator;
    ChoiceSelectCLI *_selector;
    DisplayGroupCLI *_yes_no_group;
    DisplayBoardCreatorCLI *_board_creator;
    DisplayLevelEditorCLI *_level_editor;
    DisplayLinkEditorCLI *_link_editor;
    DisplayLevelLinkEditorCLI *_level_link_editor;

public:
    DisplayGameCreatorCLI(GameCreator *creator) : _creator(creator)
    {
        _selector = new ChoiceSelectCLI(creator->get_main_menu(), true);
        _selector->set_labels({"New Level", "Link Edit", "Save", "Exit"});
        _element      = new GroupCLI("GameCreator", _selector);
        _yes_no_group = new DisplayGroupCLI(
            "Exit ?", new DisplayYesNoCLI(_creator->get_exit_yes_no()));
        _board_creator     = new DisplayBoardCreatorCLI();
        _level_editor      = new DisplayLevelEditorCLI();
        _link_editor       = new DisplayLinkEditorCLI();
        _level_link_editor = new DisplayLevelLinkEditorCLI();
    }

    void gen_string_array()
    {
        static ACState last_state = ACState::CATCH;

        if (_creator->get_ac_state() == ACState::EXIT_YES_NO) {
            _yes_no_group->gen_string_array();
            _string_array = _yes_no_group->get_string_array();
            dimensions(_yes_no_group->dimensions());
            last_state = ACState::EXIT_YES_NO;
        } else if (_creator->get_ac_state() == ACState::MENU0) {
            if (last_state != ACState::MENU0) {
                _board_creator->set_board_creator(
                    _creator->get_current_board());
            }
            _board_creator->gen_string_array();
            _string_array = _board_creator->get_string_array();
            last_state    = ACState::MENU0;
        } else if (_creator->get_ac_state() == ACState::MENU1) {
            if (last_state != ACState::MENU1) {
                _level_editor->set_level_editor(
                    _creator->get_current_level_editor());
            }
            _level_editor->gen_string_array();
            _string_array = _level_editor->get_string_array();
            last_state    = ACState::MENU1;

        } else if (_creator->get_ac_state() == ACState::MENU2) {
            if (last_state != ACState::MENU2) {
                _link_editor->set_link_editor(
                    _creator->get_current_link_editor());
            }
            _link_editor->gen_string_array();
            _string_array = _link_editor->get_string_array();
            last_state    = ACState::MENU2;
        } else if (_creator->get_ac_state() == ACState::MENU3) {
            if (last_state != ACState::MENU3) {
                _level_link_editor->set_level_link_editor(
                    _creator->get_current_level_link_editor());
            }
            _level_link_editor->gen_string_array();
            _string_array = _level_link_editor->get_string_array();
            last_state    = ACState::MENU3;
        } else {
            _element->gen_string_array();
            _string_array = _element->get_string_array();
            last_state    = ACState::CATCH;
        }
    }
};

#endif