#ifndef MODEL_AI_ALGORITHMS_PRIORITYQUEUE_HPP_
#define MODEL_AI_ALGORITHMS_PRIORITYQUEUE_HPP_

#include <algorithm>
#include <deque>
#include <functional>

template <typename T,
          typename Container = std::deque<T>,
          typename Compare   = std::less<T>>
class PriorityQueue
{
private:
    Container _queue;
    Compare _compare;

    typename Container::iterator find(T &object)
    {
        return std::find(_queue.begin(), _queue.end(), object);
    }

public:
    PriorityQueue() { _queue = Container(); }

    bool empty() { return _queue.empty(); }
    T pop()
    {
        T object = _queue.at(0);
        _queue.erase(_queue.begin());
        return object;
    }
    T &front() { return _queue.at(0); }
    void insert(T object)
    {
        size_t index = 0;
        for (T &e : _queue) {
            if (_compare(object, e))
                break;
            index++;
        }
        _queue.insert(_queue.begin() + index, object);
    }
    void erase(T &object)
    {
        auto it = find(object);
        if (it != _queue.end())
            _queue.erase(it);
    }
    const size_t size() { return _queue.size(); }
    bool contains(T &object) { return find(object) != _queue.end(); }
    void clear() { _queue.clear(); }
};

#endif // !MODEL_AI_ALGORITHMS_PRIORITYQUEUE_HPP_