#ifndef MODEL_CREATOR_LEVELEDITOR_HPP_
#define MODEL_CREATOR_LEVELEDITOR_HPP_

#include "LevelCreator.hpp"
#include "Model/AI/DefaultAI.hpp"
#include "Model/Creator/LinkEditor.hpp"
#include "Model/MoveSet/SquareMoveSet.hpp"
#include "Model/NumberSelector.hpp"

class LevelEditor : public virtual ExitYesNoContainer
{
private:
    /**
     * @brief Menu
     *
     * 1: Monster Square
     * 2: Monster Diag
     * 3: Monster Cross
     * 4: Diamond
     * 5: Ch1
     * 6: Ch2
     * 7: Ch3
     * 8: Player
     * 9: Remove
     */
    EditorOptions *_options;

    LevelCreator *_level;

    bool apply_options()
    {
        if (!_level->board()
                 ->get_square(_level->board()->cursor())
                 ->is_accessible())
            return false;
        _level->remove_game_objects();
        switch (_options->get()) {
            case 0:
                return _level->set_monster(new Monster(
                    new DefaultAI(), new SquareMoveSet(), Color::MON1));
                break;
            case 1:
                return _level->set_monster(new Monster(
                    new DefaultAI(), new DiagonalCrossMoveSet(), Color::MON2));
                break;
            case 2:
                return _level->set_monster(new Monster(
                    new DefaultAI(), new CrossMoveSet(), Color::MON3));
                break;
            case 3: return _level->set_diamond(new Diamond()); break;
            case 4: return _level->set_charger(new Charger()); break;
            case 5:
                return _level->set_charger(new Charger(ChargerType::RANDOM));
                break;
            case 6:
                return _level->set_charger(
                    new Charger(ChargerType::RANDOM_SAFE));
                break;
            case 7: return _level->set_player(); break;
            case 8: return true; break;
        }
        return false;
    }

    ActionOutput on_actionable_element_exit()
    {
        if (_ac_state == ACState::EXIT_YES_NO) {
            if (_exit_yes_no->get()) {
                return ACTION_EXIT;
            }
            return ACTION_SUCCESS;
        }
        return ACTION_FAILED;
    }

public:
    LevelEditor(Board *board)
    {
        _level = new LevelCreator();
        _level->set_board(board);
        _level->set_state_select();

        _options = new EditorOptions(9, false);
    }
    ~LevelEditor()
    {
        if (_options)
            delete _options;
        _options = nullptr;
    }

    ActionOutput internal_act_on_input(const Input &input)
    {
        ActionOutput out = ACTION_FAILED;
        out              = _options->act_on_input(input);
        if (out != ACTION_FAILED)
            return out;
        if (input & Input::ENTER) {
            if (apply_options())
                return ACTION_SUCCESS;
        } else if (_level->move_cursor(input))
            return ACTION_SUCCESS;
        else if (input & Input::EXIT) {
            ExitYesNoContainer::internal_act_on_input(input);
        }
        return ACTION_FAILED;
    }

    EditorOptions *options() { return _options; }
    LevelCreator *level() { return _level; }
};

#endif // !MODEL_CREATOR_LEVELEDITOR_HPP_