#ifndef MODEL_CHOICESELECT_HPP_
#define MODEL_CHOICESELECT_HPP_

#include <cstdlib>
#include <tuple>

#include "Model/Actionable.hpp"
#include "Util/TupleIteration.hpp"

class ChoiceSelect
{
protected:
    size_t _option;
    size_t _max;
    const size_t _init_option;
    const bool _dynamic_size;

public:
    ChoiceSelect(const size_t &max,
                 const bool &dynamic_size = true,
                 const size_t &option     = 0)
        : _max(max), _option(option), _dynamic_size(dynamic_size),
          _init_option(option)
    {
    }
    bool set(size_t option)
    {
        if (option < _max)
            _option = option;
        else
            return false;
        return true;
    }
    const size_t get() const { return _option; }
    const size_t max() const { return _max; }
    void set_max(size_t val)
    {
        // if (_dynamic_size)
        _max = val;
    }
    virtual void increment_choice() { _option = (_option + 1) % _max; }
    virtual void decrement_choice() { _option = (_option + _max - 1) % _max; }
    const bool is_dynamic() { return _dynamic_size; }
    void reset() { _option = _init_option; }
};

struct CSAction {
    virtual ActionOutput operator()(ChoiceSelect &select, const Input &input)
        = 0;
};

struct CSVAction : public CSAction {
    ActionOutput operator()(ChoiceSelect &select, const Input &input)
    {
        if (input & Input::DOWN)
            select.increment_choice();
        else if (input & Input::UP)
            select.decrement_choice();
        else
            return ACTION_FAILED;
        return ACTION_SUCCESS;
    }
};

/**
 * @brief Inverse of CSVAction
 *
 */
struct CSIVAction : public CSAction {
    ActionOutput operator()(ChoiceSelect &select, const Input &input)
    {
        if (input & Input::UP)
            select.increment_choice();
        else if (input & Input::DOWN)
            select.decrement_choice();
        else
            return ACTION_FAILED;
        return ACTION_SUCCESS;
    }
};

struct CSHAction : public CSAction {
    ActionOutput operator()(ChoiceSelect &select, const Input &input)
    {
        if (input & Input::RIGHT)
            select.increment_choice();
        else if (input & Input::LEFT)
            select.decrement_choice();
        else
            return ACTION_FAILED;
        return ACTION_SUCCESS;
    }
};

struct CSEnterExitAction : public CSAction {
    ActionOutput operator()(ChoiceSelect &select, const Input &input)
    {
        if (input & Input::ENTER)
            return ACTION_EXIT;

        return ACTION_FAILED;
    }
};

template <bool Offset = false>
struct CSButAction : virtual CSAction {
    ActionOutput operator()(ChoiceSelect &select, const Input &input)
    {

        if (input & Input::BUT0)
            return select.set(0 + (Offset ? 9 : 0)) ? ACTION_SUCCESS
                                                    : ACTION_FAILED;
        else if (input & Input::BUT1)
            return select.set(1 - (Offset ? 1 : 0)) ? ACTION_SUCCESS
                                                    : ACTION_FAILED;
        else if (input & Input::BUT2)
            return select.set(2 - (Offset ? 1 : 0)) ? ACTION_SUCCESS
                                                    : ACTION_FAILED;
        else if (input & Input::BUT3)
            return select.set(3 - (Offset ? 1 : 0)) ? ACTION_SUCCESS
                                                    : ACTION_FAILED;
        else if (input & Input::BUT4)
            return select.set(4 - (Offset ? 1 : 0)) ? ACTION_SUCCESS
                                                    : ACTION_FAILED;
        else if (input & Input::BUT5)
            return select.set(5 - (Offset ? 1 : 0)) ? ACTION_SUCCESS
                                                    : ACTION_FAILED;
        else if (input & Input::BUT6)
            return select.set(6 - (Offset ? 1 : 0)) ? ACTION_SUCCESS
                                                    : ACTION_FAILED;
        else if (input & Input::BUT7)
            return select.set(7 - (Offset ? 1 : 0)) ? ACTION_SUCCESS
                                                    : ACTION_FAILED;
        else if (input & Input::BUT8)
            return select.set(8 - (Offset ? 1 : 0)) ? ACTION_SUCCESS
                                                    : ACTION_FAILED;
        else if (input & Input::BUT9)
            return select.set(9 - (Offset ? 1 : 0)) ? ACTION_SUCCESS
                                                    : ACTION_FAILED;
        return ACTION_FAILED;
    }
};

// /**
//  * @brief Variadic Template of Actions.
//  *
//  * @tparam Actions
//  */
// template <typename... Actions>
// struct CSAggregateAction : public CSAction {
//     typedef std::tuple<Actions...> vtypes;
//     vtypes _actions;

//     ActionOutput operator()(ChoiceSelect &select, const Input &input)
//     {
//         TupleIteration::make_index_sequence<_tsize> index_seq;
//         ActionOutput out = ACTION_FAILED;
//         // for (unsigned short i(0); i < _tsize; i++)
//         for (size_t index : index_seq) {
//             out = std::get<index>(_actions)(select, input);
//             if (out != ACTION_FAILED)
//                 return out;
//         }
//         return out;
//     }

// private:
//     static const unsigned short int _tsize = sizeof...(Actions);
// };

template <typename A, typename B>
struct CSAggregateAction : public CSAction {
    A _action_a;
    B _action_b;

    ActionOutput operator()(ChoiceSelect &select, const Input &input)
    {
        ActionOutput out = _action_a(select, input);
        if (out == ACTION_FAILED)
            return _action_b(select, input);
        return out;
    }
};

template <typename Action
          = CSAggregateAction<CSHAction,
                              CSAggregateAction<CSVAction, CSEnterExitAction>>>
class ActionableChoiceSelect : public ChoiceSelect, public Actionable
{
public:
    Action action;

    ActionableChoiceSelect(const size_t &max,
                           const bool &dynamic_size = true,
                           const size_t &option     = 0)
        : ChoiceSelect(max, dynamic_size, option)
    {
    }
    virtual ActionOutput act_on_input(const Input &input)
    {
        return action(*this, input);
    }
};

class YesNo : public ActionableChoiceSelect<>
{
public:
    YesNo(bool yes = false) : ActionableChoiceSelect(2, false, yes ? 1 : 0) {}

    bool yes() { return _option == 1; }
};

class ExitYesNoContainer : public ActionableContainer
{
protected:
    YesNo *_exit_yes_no;

    virtual ActionOutput on_actionable_element_exit()
    {
        if (_ac_state == ACState::EXIT_YES_NO) {
            set_ac_state(ACState::CATCH);
            if (_exit_yes_no->get())
                return ACTION_EXIT;
            return ACTION_SUCCESS;
        }
        return ACTION_FAILED;
    }

public:
    ExitYesNoContainer() { _exit_yes_no = new YesNo(); }
    ~ExitYesNoContainer() { delete _exit_yes_no; }

    virtual ActionOutput internal_act_on_input(const Input &input)
    {
        if (input & Input::EXIT) {
            _actionable_element = _exit_yes_no;
            set_ac_state(ACState::EXIT_YES_NO);
            return ACTION_SUCCESS;
        }
        return ACTION_FAILED;
    }
    YesNo *get_exit_yes_no() { return _exit_yes_no; }
};

class ContinueYesNoContainer : public ActionableContainer
{
protected:
    YesNo *_continue_yes_no;

    virtual ActionOutput on_actionable_element_exit()
    {
        if (_ac_state == ACState::CONTINUE_YES_NO) {
            set_ac_state(ACState::CATCH);
            if (_continue_yes_no->get())
                return ACTION_CONTINUE;
            return ACTION_SUCCESS;
        }
        return ACTION_FAILED;
    }

public:
    ContinueYesNoContainer() { _continue_yes_no = new YesNo(); }
    ~ContinueYesNoContainer() { delete _continue_yes_no; }

    virtual ActionOutput internal_act_on_input(const Input &input)
    {
        if (input & Input::ENTER) {
            _actionable_element = _continue_yes_no;
            set_ac_state(ACState::CONTINUE_YES_NO);
            return ACTION_SUCCESS;
        }
        return ACTION_FAILED;
    }
    YesNo *get_continue_yes_no() { return _continue_yes_no; }
};

#endif // !MODEL_CHOICESELECT_HPP_