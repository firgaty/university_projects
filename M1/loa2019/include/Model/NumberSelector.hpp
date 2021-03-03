#ifndef MODEL_NUMBER_SELECTOR_HPP
#define MODEL_NUMBER_SELECTOR_HPP

#include <numeric>
#include <vector>

#include "Model/ChoiceSelect.hpp"
#include "Util/Math.hpp"

using ActionableDigitSelector
    = ActionableChoiceSelect<CSAggregateAction<CSIVAction, CSButAction<false>>>;

class DigitSelector : public ActionableDigitSelector
{
public:
    DigitSelector(const size_t &initial = 0)
        : ActionableDigitSelector(10, false, initial)
    {
    }
};

class NumberSelector : public ActionableChoiceSelect<
                           CSAggregateAction<CSHAction, CSEnterExitAction>>
{
protected:
    std::vector<size_t> _n_digits;
    std::vector<DigitSelector *> _digit_selectors;

    size_t _number(size_t first_digit, size_t digit_number)
    {
        size_t number = 0;
        for (size_t i = first_digit; i < first_digit + digit_number; i++) {
            number *= 10;
            number += _digit_selectors[i]->get();
        }
        return number;
    }

public:
    NumberSelector(std::vector<size_t> n_digits)
        : ActionableChoiceSelect<
            CSAggregateAction<CSHAction, CSEnterExitAction>>(
            accumulate(n_digits.begin(), n_digits.end(), 0), false),
          _n_digits(n_digits), _digit_selectors()
    {
        for (size_t n : _n_digits) {
            for (size_t i = 0; i < n; i++)
                _digit_selectors.push_back(new DigitSelector());
        }
    }

    NumberSelector(std::vector<size_t> n_digits, std::vector<size_t> values)
        : ActionableChoiceSelect<
            CSAggregateAction<CSHAction, CSEnterExitAction>>(
            accumulate(n_digits.begin(), n_digits.end(), 0), false),
          _n_digits(n_digits), _digit_selectors()
    {
        for (size_t n = 0; n < n_digits.size(); n++) {
            for (size_t i = 0; i < n_digits[n]; i++) {
                _digit_selectors.push_back(new DigitSelector(
                    (values[n] / (Math::pow(10, n_digits[n] - i - 1))) % 10));
            }
            // Get a digit value
        }
    }

    ActionOutput act_on_input(const Input &input)
    {
        ActionOutput out = action(*this, input);
        if (out != ACTION_FAILED)
            return out;
        return _digit_selectors[get()]->action(*_digit_selectors[get()], input);
    }

    std::vector<size_t> numbers()
    {
        std::vector<size_t> vec;
        size_t counter = 0;
        for (size_t n : _n_digits) {
            vec.push_back(_number(counter, n));
            counter += n;
        }
        return vec;
    }

    void set_numbers(std::vector<size_t> values)
    {
        for (size_t n = 0; n < _n_digits.size(); n++) {
            for (size_t i = 0; i < _n_digits[n]; i++) {
                _digit_selectors[n]->set(
                    (values[n] / (Math::pow(10, _n_digits[n] - i - 1))) % 10);
            }
            // Get a digit value
        }
    }
    const std::vector<size_t> &n_digits() { return _n_digits; }
    const std::vector<DigitSelector *> &digit_selectors()
    {
        return _digit_selectors;
    }
};

class UniqueNumberSelector : public NumberSelector
{
    UniqueNumberSelector(size_t digits)
        : NumberSelector(std::vector<size_t>(1, digits))
    {
    }

    size_t number() { return _number(0, _n_digits[0]); }
};

#endif // !MODEL_NUMBER_SELECTOR_HPP