#ifndef INCLUDE_MODEL_DOOR_DOOR_HPP_
#define INCLUDE_MODEL_DOOR_DOOR_HPP_

#include "Square.hpp"

class Door : public virtual Square
{
private:
    bool _goal;

public:
    Door(bool open = false, bool goal = false)
        : Square(open,
                 open ? (goal ? Color::DOOR_GOAL_OPEN : Color::DOOR_OPEN)
                      : (goal ? Color::DOOR_GOAL_CLOSE : Color::DOOR_CLOSE)),
          _goal(goal)
    {
    }
    ~Door() {}
    void open()
    {
        _accessible = true;
        set_color(_goal ? Color::DOOR_GOAL_OPEN : Color::DOOR_OPEN);
    }
    void close()
    {
        _accessible = false;
        set_color(_goal ? Color::DOOR_GOAL_CLOSE : Color::DOOR_CLOSE);
    }

    const bool is_goal() const { return _goal; }

    static bool is_this_type(const Square *o)
    {
        return (dynamic_cast<const Door *>(o) != nullptr);
    }
};

#endif // INCLUDE_MODEL_DOOR_DOOR_HPP_
