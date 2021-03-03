#include "Controller/KeyboardLayout.hpp"

const Input Layout_en_GB::operator()(const wint_t &c)
{
    switch (c) {
        case 'w': return Input::UP;
        case 'x': return Input::DOWN;
        case 'd': return Input::RIGHT;
        case 'a': return Input::LEFT;
        case 'e': return Input::UP | Input::RIGHT;
        case 'q': return Input::UP | Input::LEFT;
        case 'c': return Input::DOWN | Input::RIGHT;
        case 'z': return Input::DOWN | Input::LEFT;
        case 's': return Input::ENTER;
        case '0': return Input::BUT0;
        case '1': return Input::BUT1;
        case '2': return Input::BUT2;
        case '3': return Input::BUT3;
        case '4': return Input::BUT4;
        case '5': return Input::BUT5;
        case '6': return Input::BUT6;
        case '7': return Input::BUT7;
        case '8': return Input::BUT8;
        case '9': return Input::BUT9;
        case 'p': return Input::EXIT;
        case '\n': return Input::ENTER;
        case ' ': return Input::ENTER;
        default: return Input::ERROR;
    }
}

const Input Layout_fr_FR::operator()(const wint_t &c)
{
    switch (c) {
        case 'z': return Input::UP;
        case 'x': return Input::DOWN;
        case 'd': return Input::RIGHT;
        case 'q': return Input::LEFT;
        case 'e': return Input::UP | Input::RIGHT;
        case 'a': return Input::UP | Input::LEFT;
        case 'c': return Input::DOWN | Input::RIGHT;
        case 'w': return Input::DOWN | Input::LEFT;
        case 's': return Input::ENTER;
        case 224: return Input::BUT0;
        case '&': return Input::BUT1;
        case 233: return Input::BUT2;
        case '\"': return Input::BUT3;
        case '\'': return Input::BUT4;
        case '(': return Input::BUT5;
        case '-': return Input::BUT6;
        case 232: return Input::BUT7;
        case '_': return Input::BUT8;
        case 231: return Input::BUT9;
        case 'p': return Input::EXIT;
        case '\n': return Input::ENTER;
        case ' ': return Input::ENTER;
        default: return Input::ERROR;
    }
}

const Input Layout_en_US::operator()(const wint_t &c)
{
    switch (c) {
        case 'w': return Input::UP;
        case 'x': return Input::DOWN;
        case 'd': return Input::RIGHT;
        case 'a': return Input::LEFT;
        case 'e': return Input::UP | Input::RIGHT;
        case 'q': return Input::UP | Input::LEFT;
        case 'c': return Input::DOWN | Input::RIGHT;
        case 'z': return Input::DOWN | Input::LEFT;
        case 's': return Input::ENTER;
        case '0': return Input::BUT0;
        case '1': return Input::BUT1;
        case '2': return Input::BUT2;
        case '3': return Input::BUT3;
        case '4': return Input::BUT4;
        case '5': return Input::BUT5;
        case '6': return Input::BUT6;
        case '7': return Input::BUT7;
        case '8': return Input::BUT8;
        case '9': return Input::BUT9;
        case 'p': return Input::EXIT;
        case '\n': return Input::ENTER;
        case ' ': return Input::ENTER;
        default: return Input::ERROR;
    }
}