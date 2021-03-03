#ifndef INCLUDE_MODEL_GAMEOBJECT_MOVEABLE_HPP_
#define INCLUDE_MODEL_GAMEOBJECT_MOVEABLE_HPP_

#include <vector>

#include "GameObject.hpp"
#include "Model/MoveSet/MoveSet.hpp"

/**
 * @brief Abstract class for moveable GameObject.
 *
 */

class Moveable : public GameObject
{
protected:
    std::vector<Point2D> _past_moves;
    MoveSet *_move_set = nullptr;

    explicit Moveable(MoveSet *move_set,
                      Color c = Color::PLAYER,
                      const GameObjectType type = GameObjectType::PLAYER)
        : GameObject(c, type), _move_set(move_set)
    {
    }

public:
    virtual ~Moveable() { delete _move_set; }
    void set_move_set(MoveSet *move_set)
    {
        if (_move_set != nullptr) {
            delete _move_set;
            _move_set = nullptr;
        }

        _move_set = move_set;
    }
    const std::vector<Point2D> past_moves() const { return _past_moves; }
    MoveSet const *get_move_set() { return _move_set; }
    bool has_move_set() const { return _move_set != nullptr; }
};

#endif // INCLUDE_MODEL_GAMEOBJECT_MOVEABLE_HPP_
