#ifndef INCLUDE_MODEL_GAMEOBJECT_PLAYER_HPP_
#define INCLUDE_MODEL_GAMEOBJECT_PLAYER_HPP_

#include "Moveable.hpp"
#include "../MoveSet/SquareMoveSet.hpp"

class Player : public virtual Moveable
{
public:
    Player()
        : Moveable(new SquareMoveSet(), Color::PLAYER, GameObjectType::PLAYER)
    {
    }
    static bool is_this_type(const GameObject *o)
    {
        return (dynamic_cast<const Player *>(o) != nullptr);
    }
};

#endif // INCLUDE_MODEL_GAMEOBJECT_PLAYER_HPP_
