#ifndef MODEL_CREATOR_LEVELLINKEDITOR_HPP_
#define MODEL_CREATOR_LEVELLINKEDITOR_HPP_

#include "Model/ChoiceSelect.hpp"
#include "Model/Game.hpp"
#include "Model/NumberSelector.hpp"

using EditorOptions = ActionableChoiceSelect<CSButAction<true>>;

class LevelLinkEditor : public virtual ExitYesNoContainer
{
private:
    Game *_game;
    Level *_level;
    Point2D _pa, _pb;
    size_t _ida, _idb;
    bool _state, _select;
    ActionableChoiceSelect<CSIVAction> *_number_selector;

    /*
    1: Add
    2: Remove
    */
    EditorOptions *_options;

    bool apply_options()
    {
        // switch (_options->get()) {
        //     case 0:
        //         _game->add_link(_ida, _pa, _idb, _pb);
        //         return ACTION_SUCCESS;
        //     case 1:
        //         return ACTION_SUCCESS;
        // }
        _game->add_link(_ida, _pa, _idb, _pb);
        return ACTION_SUCCESS;
        // return ACTION_FAILED;
    }

    ActionOutput on_actionable_element_exit()
    {
        if (_ac_state == ACState::EXIT_YES_NO) {
            if (_exit_yes_no->get())
                return ACTION_EXIT;
        } else
            return ACTION_SUCCESS;
        return ACTION_FAILED;
    }

public:
    LevelLinkEditor()
    {
        _game            = nullptr;
        _level           = nullptr;
        _state           = false;
        _select          = true;
        _pa              = {-1, -1};
        _pb              = {-1, -1};
        _ida             = 0;
        _idb             = 0;
        _options         = new EditorOptions(2, false, 0);
        _number_selector = new ActionableChoiceSelect<CSIVAction>(999, true, 0);
    }

    LevelLinkEditor(Game *game) : LevelLinkEditor()
    {
        _game  = game;
        _level = _game->get_levels()->at(0);
        _number_selector->set_max(_game->get_levels()->size());
    }
    ~LevelLinkEditor()
    {
        if (_number_selector)
            delete _number_selector;
    }

    ActionOutput internal_act_on_input(const Input &input)
    {
        if (input & Input::EXIT) {
            ExitYesNoContainer::internal_act_on_input(input);
            return ACTION_FAILED;
        }
        ActionOutput out = ACTION_FAILED;
        if (_select) {
            if (input & Input::ENTER) {
                if (!_state)
                    _ida = _number_selector->get();
                else
                    _idb = _number_selector->get();
                _select = false;
                _level  = _game->get_levels()->at(_number_selector->get());
                return ACTION_SUCCESS;
            }
            out    = _number_selector->act_on_input(input);
            _level = _game->get_levels()->at(_number_selector->get());

            return out;
        }
        // out = _options->act_on_input(input);
        if (input & Input::ENTER) {
            Point2D_u coord = _level->board()->cursor();
            Square *s;
            if (!(s = _level->board()->get_square(coord)))
                return ACTION_FAILED;
            if (!_state && Door::is_this_type(s)) { // select door
                _pa     = coord;
                _state  = true;
                _select = true;              // set to select accessible square
            } else if (s->is_accessible()) { // select accessible square
                _pb = coord;
                if (apply_options()) {
                    _state  = false; // set to select diamond
                    _select = true;
                    return ACTION_SUCCESS;
                }
            }
            return ACTION_FAILED;
        } else if (_level->move_cursor(
                       input,
                       BoardSeekOption::ALL)) // Change BoardSeekOption.
            return ACTION_SUCCESS;
        return ACTION_FAILED;
    }

    // EditorOptions *get_options() { return _options; }
    Game *get_game() { return _game; }
    Level *get_level() { return _level; }
    bool get_state() const { return _state; }
    bool get_select() const { return _select; }
    const Point2D_u get_point() const { return _pa; }
    const size_t get_id() const { return _ida; }
    ActionableChoiceSelect<CSIVAction> *get_number_selector()
    {
        return _number_selector;
    }
};

#endif