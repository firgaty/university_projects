#include "Model/Board/Square.hpp"

Square::Square() : Square(true, Color::EMPTY) {}
Square::Square(bool accessible)
    : Square(accessible, accessible ? Color::EMPTY : Color::WALL1)
{
}
Square::Square(bool accessible, Color color)
    : Square(accessible, color, nullptr)
{
}
Square::Square(bool accessible, Color color, const GameObject *object)
    : Colored(color)
{
    _accessible = accessible;
    _objects    = std::vector<const GameObject *>();
    if (object != nullptr)
        _objects.push_back(object);
}

const std::vector<const GameObject *> Square::objects() const
{
    return _objects;
}
const bool Square::is_accessible() const { return _accessible; }
void Square::add_object(const GameObject *o)
{
    if (o == nullptr)
        return;
    _objects.push_back(o);
}
const GameObject *Square::remove_object(const std::size_t &index)
{
    if (index >= _objects.size())
        return nullptr;
    return remove_object(_objects.begin() + index);
}

const GameObject *Square::remove_object(const GameObject *o)
{
    if (has_object(o))
        return remove_object(index_of(o));
    return nullptr;
}
const GameObject *
Square::remove_object(const std::vector<const GameObject *>::iterator &it)
{
    const GameObject *o = *it;
    _objects.erase(it);    return o;
}

const GameObject *Square::remove_last()
{
    const GameObject *o = get_last();
    if (_objects.size() > 0)
        _objects.pop_back();
    return o;
}

const GameObject *Square::get(size_t index) const
{
    if (size() < index)
        return nullptr;
    return _objects.at(index);
}
const GameObject *Square::get_last() const
{
    if (is_empty())
        return nullptr;
    return _objects.back();
}

bool Square::is_empty() const { return _objects.empty(); }
const size_t Square::size() const { return _objects.size(); }

bool Square::has_object(const GameObject *o)
{
    return it_of(o) != _objects.end();
}

std::size_t Square::index_of(const GameObject *o)
{
    return std::distance(_objects.begin(), it_of(o));
}
std::vector<const GameObject *>::iterator Square::it_of(const GameObject *o)
{
    return std::find(_objects.begin(), _objects.end(), o);
}
