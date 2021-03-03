#ifndef MODEL_CREATOR_LEVELCREATORMAIN_HPP_
#define MODEL_CREATOR_LEVELCREATORMAIN_HPP_

#include "Model/Board/BoardContainer.hpp"
#include "Model/Board/Door.hpp"
#include "Model/NumberSelector.hpp"

using EditorOptions = ActionableChoiceSelect<CSButAction<true>>;

class BoardCreator : public ExitYesNoContainer, public BoardContainer
{
private:
    NumberSelector *_number_selector;
    /**
     * @brief Menu
     *
     * 0: Empty
     * 1: Wall
     * 2: Door closed
     * 3: Door open
     */
    EditorOptions *_board_options; // Menu1

    ActionOutput on_actionable_element_exit()
    {
        ActionOutput out = ACTION_FAILED;
        if (out != ACTION_FAILED)
            return out;
        if (_ac_state == ACState::EXIT_YES_NO) {
            if (_exit_yes_no->get()) {
                return ACTION_EXIT;
            }
            set_ac_state(ACState::CATCH);
            return ACTION_SUCCESS;
        }
        if (_ac_state == ACState::MENU0) {
            if (_number_selector->numbers()[0] > 2
                && _number_selector->numbers()[1] > 2) {
                set_board(new Board(_number_selector->numbers()[0],
                                    _number_selector->numbers()[1]));
                _board->show_cursor(true);
                set_ac_state(ACState::CATCH);
                return ACTION_SUCCESS;
            } else
                return ACTION_FAILED;
        }
        return ACTION_FAILED;
    }

    void set_board_element()
    {
        switch (_board_options->get()) {
            case 0:
                _board->set_square(_board->cursor(),
                                   new Square(true, Color::EMPTY));
                break;
            case 1:
                _board->set_square(_board->cursor(),
                                   new Square(false, Color::WALL1));
                break;
            case 2:
                _board->set_square(_board->cursor(), new Door(false));
                break;
            case 3: _board->set_square(_board->cursor(), new Door(true)); break;
            case 4:
                _board->set_square(_board->cursor(), new Door(false, true));
                break;
            case 5:
                _board->set_square(_board->cursor(), new Door(true, true));
                break;
        }
    }

public:
    BoardCreator()
    {
        _number_selector = new NumberSelector({2, 3}, {10, 20});
        _board_options   = new EditorOptions(6, false, 0);
        set_actionable_element(_number_selector);
        set_ac_state(ACState::MENU0);
    }

    ActionOutput internal_act_on_input(const Input &input)
    {
        ActionOutput out = _board_options->act_on_input(input);
        if (out != ACTION_FAILED)
            return out;
        if (input & Input::EXIT) {
            set_actionable_element(_exit_yes_no);
            _exit_yes_no->reset();
            set_ac_state(ACState::EXIT_YES_NO);
        }
        if (out != ACTION_FAILED)
            return out;
        if (move_cursor(input, BoardSeekOption::ALL))
            return ACTION_SUCCESS;
        if (input & Input::ENTER) {
            set_board_element();
            return ACTION_SUCCESS;
        }

        return ACTION_FAILED;
    }

    NumberSelector *number_selector() { return _number_selector; }
    ChoiceSelect *board_options() { return _board_options; }
};

#endif // !MODEL_CREATOR_LEVELCREATORMAIN_HPP_