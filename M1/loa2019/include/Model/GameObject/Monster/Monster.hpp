#ifndef INCLUDE_GAMEOBJECT_MONSTER_MONSTER_HPP_
#define INCLUDE_GAMEOBJECT_MONSTER_MONSTER_HPP_

#include "Model/AI/AI.hpp"
#include "Model/GameObject/Moveable.hpp"
#include "Model/MoveSet/SquareMoveSet.hpp"

class Monster : public Moveable
{
protected:
    AI *_ai = nullptr;

public:
    Monster(AI *ai, MoveSet *move_set = nullptr, Color color = Color::MON1)
        : Moveable(move_set, color, GameObjectType::MONSTER), _ai(ai)
    {
        if (_move_set == nullptr)
            this->set_move_set(new SquareMoveSet());
    }
    virtual ~Monster() { delete _ai; }

    AI const *get_ai() { return _ai; }

    virtual const Point2D
    move(const Point2D &coord, const Point2D &goal, const Board *board)
    {
        return _ai->move(coord, goal, board, _move_set);
    }

    static bool is_this_type(const GameObject *o)
    {
        return (dynamic_cast<const Monster *>(o) != nullptr);
    }
};

#endif // INCLUDE_GAMEOBJECT_MONSTER_MONSTER_HPP_