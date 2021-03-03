#ifndef MODEL_ACTIONABLE_HPP_
#define MODEL_ACTIONABLE_HPP_

#include "Controller/Input.hpp"

#include <iostream>

enum ActionOutput {
    ACTION_FAILED = 0,
    ACTION_SUCCESS,
    ACTION_EXIT,
    ACTION_CONTINUE
};

class Actionable
{
public:
    virtual ActionOutput act_on_input(const Input &input) = 0;
};

enum class ACState { CATCH, THROUGH, EXIT_YES_NO, CONTINUE_YES_NO, MENU0, MENU1, MENU2, MENU3, MENU4};

class ActionableContainer : public Actionable
{
protected:
    ACState _ac_state;
    Actionable *_actionable_element;

    void set_ac_state(ACState state) { _ac_state = state; }
    void set_actionable_element(Actionable *e, bool del_prev = false)
    {
        if (del_prev && (_actionable_element))
            delete _actionable_element;
        _actionable_element = e;
    }

    virtual ActionOutput on_actionable_element_exit() = 0;

public:
    ActionableContainer() : _ac_state(ACState::CATCH)
    {
        _actionable_element = nullptr;
    }

    virtual ActionOutput act_on_input(const Input &input)
    {
        if (_ac_state == ACState::CATCH) {
            return internal_act_on_input(input);
        } else {
            ActionOutput output = _actionable_element->act_on_input(input);
            if (output == ACTION_EXIT) {
                output    = on_actionable_element_exit();
                _ac_state = ACState::CATCH;
                return output;
            }
        }
        return ACTION_FAILED;
    }

    virtual ActionOutput internal_act_on_input(const Input &input)
    {
        return ACTION_FAILED;
    }

    ACState get_ac_state() { return _ac_state; }
};

#endif // !MODEL_ACTIONABLE_HPP_