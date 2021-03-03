#ifndef INCLUDE_CONTROLLER_CONTROLLERCLI_HPP_
#define INCLUDE_CONTROLLER_CONTROLLERCLI_HPP_

#include <cwchar>
#include <stdio.h>
#include <termios.h>

static struct termios old, current;

#include "ControllerBase.hpp"
#include "Input.hpp"
#include "KeyboardLayout.hpp"

template <typename L = Layout_en_GB>
class ControllerKeyboard : public virtual ControllerBase
{
    L layout;

public:
    ControllerKeyboard() {}
    virtual ~ControllerKeyboard() {}
    const Input input()
    {
        bool echo = true;
        while (1) {
            // char c = getch(false);
            wint_t c = getch(echo);
            if (c == 27) {
                if (c = getch(echo) != 91)
                    return Input::ERROR;
                c = getch(echo);
                switch (c) {
                    case 'A': return Input::UP;
                    case 'B': return Input::DOWN;
                    case 'C': return Input::RIGHT;
                    case 'D': return Input::LEFT;
                    default: return Input::ERROR;
                }
            }
            return layout(c);
        }
    }
    wint_t getch(int echo)
    {
        wint_t ch;
        init_termios(echo);
        // ch = getchar();
        ch = getwchar();
        reset_termios();
        return ch;
    }
    void init_termios(int echo)
    {
        tcgetattr(0, &old);         /* grab old terminal i/o settings */
        current = old;              /* make new settings same as old settings */
        current.c_lflag &= ~ICANON; /* disable buffered i/o */
        if (echo)
            current.c_lflag |= ECHO; /* set echo mode */
        else
            current.c_lflag &= ~ECHO; /* set no echo mode */
        tcsetattr(
            0, TCSANOW, &current); /* use these new terminal i/o settings now */
    }
    void reset_termios() { tcsetattr(0, TCSANOW, &old); }
};

#endif // INCLUDE_CONTROLLER_CONTROLLERCLI_HPP_
