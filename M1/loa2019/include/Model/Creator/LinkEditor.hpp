#ifndef MODEL_CREATOR_LINKEDITOR_HPP_
#define MODEL_CREATOR_LINKEDITOR_HPP_

#include "Model/ChoiceSelect.hpp"
#include "Model/Creator/LevelCreator.hpp"

class LinkEditor : public virtual ExitYesNoContainer
{
private:
    LevelCreator *_level;
    Point2D _p_diamond, _p_door;
    bool _state;

    /*
    1: Add
    2: Remove
    */
    EditorOptions *_options;

    bool apply_options()
    {
        switch (_options->get()) {
            case 0:
                _level->set_link(_p_diamond, _p_door);
                return ACTION_SUCCESS;
            case 1:
                _level->remove_link(_p_diamond, _p_door);
                return ACTION_SUCCESS;
        }
        return ACTION_FAILED;
    }

    ActionOutput on_actionable_element_exit()
    {
        if (_ac_state == ACState::EXIT_YES_NO) {
            if (_exit_yes_no->get())
                return ACTION_EXIT;
        }
        return ACTION_FAILED;
    }

public:
    LinkEditor()
    {
        _level     = nullptr;
        _state     = false;
        _p_diamond = {-1, -1};
        _p_door    = {-1, -1};
        _options   = new EditorOptions(2, false, 0);
    }

    LinkEditor(LevelCreator *level) : LinkEditor() { _level = level; }

    ActionOutput internal_act_on_input(const Input &input)
    {
        ActionOutput out = ACTION_FAILED;
        out              = _options->act_on_input(input);
        if (out != ACTION_FAILED)
            return out;
        if (input & Input::ENTER) {
            Point2D_u coord = _level->board()->cursor();
            Square *s;
            if (!(s = _level->board()->get_square(coord)))
                return ACTION_FAILED;
            if (!_state && !s->is_empty()
                    && s->get(0)->game_object_type()
                           == GameObjectType::DIAMOND) { // select diamond
                _p_diamond = coord;
                _state     = true;              // set to select door
            } else if (Door::is_this_type(s)) { // select door
                _p_door = coord;
                if (apply_options()) {
                    _state = false; // set to select diamond
                    return ACTION_SUCCESS;
                }
            }
            return ACTION_FAILED;
        } else if (!_state
                   && _level->move_cursor(input, BoardSeekOption::ALL)) // Change BoardSeekOption.
            return ACTION_SUCCESS;
        else if (_level->move_cursor(input, BoardSeekOption::ALL)) // Change BoardSeekOption.
            return ACTION_SUCCESS;

        else if (input & Input::EXIT) {
            ExitYesNoContainer::internal_act_on_input(input);
        }
        return ACTION_FAILED;
    }

    EditorOptions *get_options() { return _options; }
    Level *get_level() { return _level; }
    bool get_state() const { return _state; }
    const Point2D_u get_point() const { return _p_diamond; }
};

#endif