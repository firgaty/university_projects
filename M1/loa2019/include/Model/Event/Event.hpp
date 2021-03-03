#ifndef EVENT_
#define EVENT_

#include <list>

#include "Model/GameObject/ChargerType.hpp"
#include "Model/GameObject/GameObject.hpp"
#include "Util/Point2D.hpp"

enum class BoardEventType { OBJECT, DOOR, ND };

struct BoardEvent {
    BoardEvent(const BoardEventType type,
               const Point2D_u &coord,
               const GameObject *object)
        : _type(type), _coord(Point2D_u(coord)), _object(object)
    {
    }
    BoardEvent(const BoardEvent &e)
        : _type(e._type), _coord(e._coord), _object(e._object)
    {
    }
    BoardEvent()
        : _type(BoardEventType::ND), _coord(Point2D_u()), _object(nullptr)
    {
    }

    const BoardEventType _type;
    const Point2D_u _coord;
    const GameObject *_object;
};

enum class LevelEventType {
    DOOR,
    LOSE,
    NO_MONSTER,
    NO_DIAMONDS,
    NO_CHARGER,
    DIAMOND,
    CHARGER,
    ND
};

/**
 * @brief Body to simulate a union.
 *
 */
struct LevelEventBody {
    const Point2D_u _coord;
    const ChargerType _charger_type = ChargerType::NORMAL;

    LevelEventBody() {}
    LevelEventBody(const Point2D_u coord) : _coord(coord) {}
    LevelEventBody(const ChargerType type) : _charger_type(type) {}
    ~LevelEventBody() {}
};

// TODO
struct LevelEvent {
    const LevelEventType _type;
    const LevelEventBody _body;
};

template <typename T>
class EventQueue
{
private:
    std::list<T> _list;
    size_t _size;

public:
    EventQueue();
    ~EventQueue();

    void push_back(const T);
    const T pop_front();
    void flush();

    bool empty();
    const size_t size();
    const T &front();
};

template <typename T>
EventQueue<T>::EventQueue()
{
    _list = std::list<T>();
    _size = 0;
}
template <typename T>
EventQueue<T>::~EventQueue()
{
    _list.clear();
}

template <typename T>
void EventQueue<T>::push_back(const T e)
{
    _list.push_back(e);
    _size++;
}
template <typename T>
const T EventQueue<T>::pop_front()
{
    const T e(_list.front());
    _list.pop_front();
    _size--;
    return e;
}
template <typename T>
void EventQueue<T>::flush()
{
    _list.clear();
    _size = 0;
}

template <typename T>
bool EventQueue<T>::empty()
{
    return _size == 0;
}
template <typename T>
const size_t EventQueue<T>::size()
{
    return _size;
}
template <typename T>
const T &EventQueue<T>::front()
{
    return _list.front();
}

using BoardEventQueue = EventQueue<BoardEvent>;
using LevelEventQueue = EventQueue<LevelEvent>;

#endif // EVENT_
