#ifndef MODEL_CREATOR_GAMECREATOR_HPP_
#define MODEL_CREATOR_GAMECREATOR_HPP_

#include "Model/ChoiceSelect.hpp"
#include "Model/Creator/BoardCreator.hpp"
#include "Model/Creator/LevelCreator.hpp"
#include "Model/Creator/LevelEditor.hpp"
#include "Model/Creator/LevelLinkEditor.hpp"
#include "Model/Creator/LinkEditor.hpp"
#include "Model/FileController/FileWriter.hpp"
#include "Model/Game.hpp"

class GameCreator : public ExitYesNoContainer
{
    using MainMenu = ActionableChoiceSelect<CSVAction>;

private:
    // 0: Add Level _ 1: Add Level_Link _ 2: Save _ 3: Exit
    ActionableChoiceSelect<CSVAction> *_main_menu;
    BoardCreator *_current_board;
    LevelCreator *_current_level;
    LevelEditor *_current_level_editor;
    LinkEditor *_current_link_editor;
    LevelLinkEditor *_current_level_link_editor;
    Game *_game;

public:
    GameCreator()
    {
        _main_menu                 = new MainMenu(4, false);
        _game                      = new Game();
        _current_board             = nullptr;
        _current_level             = nullptr;
        _current_level_editor      = nullptr;
        _current_link_editor       = nullptr;
        _current_level_link_editor = nullptr;
    }
    ~GameCreator()
    {
        if (_current_board)
            delete _current_board;
        if (_current_level)
            delete _current_level;
        if (_current_level_editor)
            delete _current_level_editor;
        if (_current_link_editor)
            delete _current_link_editor;
        if (_current_level_link_editor)
            delete _current_level_link_editor;
        delete _main_menu;
        delete _game;
    }

    virtual ActionOutput act_on_input(const Input &input)
    {
        if (_ac_state == ACState::CATCH) {
            return internal_act_on_input(input);
        } else {
            ActionOutput output = _actionable_element->act_on_input(input);
            if (output == ACTION_EXIT) {
                output = on_actionable_element_exit();
                return output;
            }
        }
        return ACTION_FAILED;
    }

    ActionOutput internal_act_on_input(const Input &input)
    {
        ActionOutput out = _main_menu->act_on_input(input);
        if (out != ACTION_FAILED)
            return out;

        switch (input) {
            case Input::ENTER:
                switch (_main_menu->get()) {
                    case 0:
                        set_ac_state(ACState::MENU0);
                        _current_board = new BoardCreator();
                        set_actionable_element(_current_board);
                        return ACTION_SUCCESS;
                        break;
                    case 1:
                        if (_game->get_levels()->size() == 0)
                            return ACTION_SUCCESS;
                        if (_current_level_link_editor)
                            delete _current_level_link_editor;
                        _current_level_link_editor = new LevelLinkEditor(_game);
                        set_actionable_element(_current_level_link_editor);
                        set_ac_state(ACState::MENU3);
                        return ACTION_SUCCESS;
                        break;
                    case 2: {
                        if (_game->get_levels()->size() == 0)
                            break;
                        _game->set_current_level(0);
                        FileWriter fw;
                        fw.writeBoardFile(_game, "save.game");
                        return ACTION_SUCCESS;
                    } break;
                    case 3:
                        return ExitYesNoContainer::internal_act_on_input(
                            Input::EXIT);
                        break;
                }
        }
        return out;
    }

    ActionOutput on_actionable_element_exit()
    {
        ActionOutput out = ACTION_FAILED;
        out              = ExitYesNoContainer::on_actionable_element_exit();
        if (out != ACTION_FAILED)
            return out;
        else if (_ac_state == ACState::MENU0) {
            set_ac_state(ACState::MENU1);
            if (_current_level_editor)
                delete _current_level_editor;
            _current_level_editor = new LevelEditor(_current_board->board());
            set_actionable_element(_current_level_editor);
            return ACTION_SUCCESS;
        } else if (_ac_state == ACState::MENU1) {
            set_ac_state(ACState::MENU2);
            if (_current_link_editor)
                delete _current_link_editor;
            _current_link_editor
                = new LinkEditor(_current_level_editor->level());
            set_actionable_element(_current_link_editor);
            return ACTION_SUCCESS;
        } else if (_ac_state == ACState::MENU2) {
            set_ac_state(ACState::CATCH);
            _game->add_level(_current_level_editor->level());
            delete _current_link_editor;
            _current_link_editor = nullptr;
            return ACTION_SUCCESS;
        } else if (_ac_state == ACState::MENU3) { // TODO: Add Level Link
            set_ac_state(ACState::CATCH);
            return ACTION_SUCCESS;
        }
        return ACTION_FAILED;
    }

    MainMenu *get_main_menu() { return _main_menu; }
    BoardCreator *get_current_board() { return _current_board; }
    LevelCreator *get_current_level() { return _current_level; }
    LevelEditor *get_current_level_editor() { return _current_level_editor; }
    LinkEditor *get_current_link_editor() { return _current_link_editor; }
    LevelLinkEditor *get_current_level_link_editor()
    {
        return _current_level_link_editor;
    }
};

#endif // !MODEL_CREATOR_GAMECREATOR_HPP_
