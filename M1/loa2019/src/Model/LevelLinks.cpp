#include <algorithm>

#include "Model/LevelLinks.hpp"

void LevelLinks::set(const size_t from,
                     const Point2D_u from_coord,
                     const size_t to,
                     const Point2D_u to_coord,
                     bool bothways)
{
    _set(from, from_coord, to, to_coord);
    if (bothways)
        _set(to, to_coord, from, from_coord);
}

void LevelLinks::_set(const size_t from,
                      const Point2D_u from_coord,
                      const size_t to,
                      const Point2D_u to_coord)
{
    if (has(from, from_coord)) {
        get_link(from, from_coord)._to = SquareID(to, to_coord);
        return;
    }
    _links.push_back(LevelLink(from, from_coord, to, to_coord));
}

void LevelLinks::remove_from(const size_t &id, const Point2D_u &coord)
{
    auto it = it_from(id, coord, true);
    if (it != _links.end())
        _links.erase(it);
}
void LevelLinks::remove_from(const size_t &id)
{
    auto begin = _links.begin();
    while (true) {
        auto it = it_from(id, begin, true);
        if (it != _links.end()) {
            _links.erase(it);
            begin = it;
        } else
            return;
    }
}
void LevelLinks::remove_to(const size_t &id, const Point2D_u &coord)
{
    auto it = it_from(id, coord, false);
    if (it != _links.end())
        _links.erase(it);
}
void LevelLinks::remove_to(const size_t &id)
{
    auto begin = _links.begin();
    while (true) {
        auto it = it_from(id, begin, false);
        if (it != _links.end()) {
            _links.erase(it);
            begin = it;
        } else
            return;
    }
}
void LevelLinks::remove(const size_t &id, const Point2D_u &coord)
{
    remove_from(id, coord);
    remove_to(id, coord);
}
void LevelLinks::remove(const size_t &id)
{
    remove_from(id);
    remove_to(id);
}

void LevelLinks::decrement_level_id(const size_t &index)
{
    for (auto e : _links) {
        if (e._from._id >= index)
            e._from._id--;
        if (e._to._id >= index)
            e._to._id--;
    }
}

bool LevelLinks::has(const size_t &id, const Point2D_u &coord, bool from)
{
    auto it = it_from(id, coord, from);
    return it != _links.end();
}
const SquareID &LevelLinks::get(const size_t &id, const Point2D_u &coord)
{
    return it_from(id, coord)->_to;
}

LevelLink &
LevelLinks::get_link(const size_t &id, const Point2D_u &coord, bool from)
{
    return *it_from(id, coord, from);
}

std::list<LevelLink>::iterator LevelLinks::it_from(
    const size_t &id, const std::list<LevelLink>::iterator &begin, bool from)
{
    return std::find_if(begin, _links.end(), [id, from](const LevelLink &s) {
        return (from ? s._from : s._to)._id == id;
    });
}

std::list<LevelLink>::iterator
LevelLinks::it_from(const size_t &id, const Point2D_u &coord, bool from)
{
    const SquareID d(id, coord);
    return std::find_if(
        _links.begin(), _links.end(), [d, from](const LevelLink &s) {
            return (from ? s._from : s._to) == d;
        });
}

const std::list<LevelLink> LevelLinks::get_links() const{
  return _links;
}
