#ifndef INCLUDE_MODEL_GAMEOBJECT_GAMEOBJECTSTATE_HPP_
#define INCLUDE_MODEL_GAMEOBJECT_GAMEOBJECTSTATE_HPP_

#include <algorithm>
#include <type_traits>

#include "Charger.hpp"
#include "Diamond.hpp"
#include "GameObject.hpp"
#include "Monster/Monster.hpp"
#include "Moveable.hpp"
#include "Player.hpp"

/**
 * @brief Template for GameObject states.
 *
 * Any _object pointer will be deleted when a GameObjectState is.
 *
 * @tparam T GameObject based object.
 */

template <typename T>
struct GameObjectState {
    GameObjectState(T object,
                    Point2D_u coord,
                    Point2D_u coord_init,
                    bool state = true);
    GameObjectState(T object, Point2D_u coord, bool state = true);
    ~GameObjectState();
    T _object;
    Point2D_u _coord      = Point2D_u();
    Point2D_u _coord_init = Point2D_u();
    bool _state           = true;
};

template <typename T>
GameObjectState<T>::GameObjectState(T object, Point2D_u coord, bool state)
    : _state(state), _coord(coord), _coord_init(coord), _object(object)
{
}

template <typename T>
GameObjectState<T>::GameObjectState(T object,
                                    Point2D_u coord,
                                    Point2D_u coord_init,
                                    bool state)
    : _state(state), _coord(coord), _coord_init(coord_init), _object(object)
{
}
template <typename T>
GameObjectState<T>::~GameObjectState()
{
}

using PlayerObjectState   = GameObjectState<Player *>;
using MoveableObjectState = GameObjectState<Moveable *>;
using MonsterObjectState  = GameObjectState<Monster *>;
using ChargerObjectState  = GameObjectState<Charger *>;
using DiamondObjectState  = GameObjectState<Diamond *>;

/**
 * @brief GameObjectState storage class.
 *
 * The GameObject stored in any GameObjectState is deleted if
 * removed or if the GameObjectStateVector is destroyed.
 *
 * @tparam T
 */
template <typename T>
class GameObjectStateVector
{

private:
    mutable std::vector<GameObjectState<T>> _objects;

public:
    GameObjectStateVector();
    ~GameObjectStateVector();

    void add(GameObjectState<T> object);
    void remove(const GameObject *object);
    void remove(const Point2D_u &p);
    bool has(const GameObject *object);
    bool has(const Point2D_u &p);
    GameObjectState<T> &get(const GameObject *object);
    GameObjectState<T> &get(const Point2D_u &p);
    GameObjectState<T> &get(const size_t &index) { return _objects[index]; }
    const std::vector<GameObjectState<T>> &get_vector() const;
    bool all_states_false();
    const size_t size() { return _objects.size(); }

private:
    typename std::vector<GameObjectState<T>>::iterator
    it_from(const Point2D_u &coord)
    {
        return std::find_if(_objects.begin(),
                            _objects.end(),
                            [&coord](const GameObjectState<T> &s) {
                                return s._coord == coord;
                            });
    }
    typename std::vector<GameObjectState<T>>::iterator
    it_from(const GameObject *object)
    {
        return std::find_if(_objects.begin(),
                            _objects.end(),
                            [&object](const GameObjectState<T> &s) {
                                return s._object == object;
                            });
    }
    static const bool IS_POINTER = std::is_pointer<T>::value;
};

template <typename T>
GameObjectStateVector<T>::GameObjectStateVector()
{
    _objects = std::vector<GameObjectState<T>>();
}

template <typename T>
GameObjectStateVector<T>::~GameObjectStateVector()
{
    if (IS_POINTER)
        for (GameObjectState<T> e : _objects)
            if ((e._object))
                delete e._object;
}

template <typename T>
void GameObjectStateVector<T>::add(GameObjectState<T> object)
{
    _objects.push_back(object);
}

template <typename T>
void GameObjectStateVector<T>::remove(const GameObject *object)
{
    auto it = it_from(object);
    if (it == _objects.end())
        return;
    if (IS_POINTER)
        delete it->_object;
    _objects.erase(it);
}
template <typename T>
void GameObjectStateVector<T>::remove(const Point2D_u &coord)
{
    auto it = it_from(coord);
    if (it == _objects.end())
        return;
    if (IS_POINTER)
        delete it->_object;
    _objects.erase(it);
}

template <typename T>
bool GameObjectStateVector<T>::has(const GameObject *object)
{
    return it_from(object) != _objects.end();
}
template <typename T>
bool GameObjectStateVector<T>::has(const Point2D_u &p)
{
    return it_from(p) != _objects.end();
}

template <typename T>
GameObjectState<T> &GameObjectStateVector<T>::get(const GameObject *object)
{
    return *it_from(object);
}
template <typename T>
GameObjectState<T> &GameObjectStateVector<T>::get(const Point2D_u &coord)
{
    return *it_from(coord);
}

template <typename T>
const std::vector<GameObjectState<T>> &
GameObjectStateVector<T>::get_vector() const
{
    return _objects;
}

template <typename T>
bool GameObjectStateVector<T>::all_states_false()
{
    for (auto e : _objects)
        if (e._state)
            return false;
    return true;
}

using PlayerObjectStateVector   = GameObjectStateVector<Player *>;
using MoveableObjectStateVector = GameObjectStateVector<Moveable *>;
using MonsterObjectStateVector  = GameObjectStateVector<Monster *>;
using ChargerObjectStateVector  = GameObjectStateVector<Charger *>;
using DiamondObjectStateVector  = GameObjectStateVector<Diamond *>;

#endif // !INCLUDE_MODEL_GAMEOBJECT_GAMEOBJECTSTATE_HPP_