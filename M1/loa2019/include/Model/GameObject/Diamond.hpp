#ifndef INCLUDE_MODEL_GAMEOBJECT_DIAMOND_HPP_
#define INCLUDE_MODEL_GAMEOBJECT_DIAMOND_HPP_

#include "GameObject.hpp"

class Diamond : public virtual GameObject
{
public:
    Diamond() : GameObject(Color::DIAMS, GameObjectType::DIAMOND) {}
    ~Diamond() {}
    static bool is_this_type(const GameObject *o)
    {
        return (dynamic_cast<const Diamond *>(o) != nullptr);
    }
};

#endif // ! INCLUDE_MODEL_GAMEOBJECT_DIAMOND_HPP_