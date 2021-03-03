#ifndef INCLUDE_MODEL_GAMEOBJECT_GAMEOBJECT_HPP_
#define INCLUDE_MODEL_GAMEOBJECT_GAMEOBJECT_HPP_

#include <string>
#include <vector>

#include "Model/Colored.hpp"
#include "Util/Point2D.hpp"

enum class GameObjectType {
    DIAMOND,
    MONSTER,
    CHARGER,
    PLAYER
};

/**
 * @brief Abstract class GameObject
 *
 * For objects that will be contained by Square objects.
 */
class GameObject : public Colored
{
protected:
    GameObject(const Color c             = Color::DIAMS,
               const GameObjectType type = GameObjectType::PLAYER)
        : Colored(c), _game_object_type(type)
    {
    }
    const GameObjectType _game_object_type;

public:
    virtual ~GameObject() {}

    const GameObjectType game_object_type() const { return _game_object_type; }
};

#endif // INCLUDE_MODEL_GAMEOBJECT_GAMEOBJECT_HPP_