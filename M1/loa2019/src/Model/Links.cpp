#include "Model/Links.hpp"

Links::Links() {}
Links::~Links() {}

void Links::add(const Link l)
{
    if (!exists(l))
        _links.push_back(l);
}
// TODO: test
void Links::add(const Diamond *diamond,
                const Point2D_u diamond_coord,
                Door *door,
                const Point2D_u door_coord)
{
    add(Link{diamond, diamond_coord, door, door_coord});
}

void Links::remove(const Diamond *const d)
{
    while (true) {
        auto it = std::find_if(_links.begin(),
                               _links.end(),
                               [&d](const Link &s) { return s._diamond == d; });
        if (it == _links.end())
            return;
        _links.erase(it);
    }
}
void Links::remove(const Door *const d)
{
    while (true) {
        auto it = std::find_if(_links.begin(),
                               _links.end(),
                               [&d](const Link &s) { return s._door == d; });
        if (it == _links.end())
            return;
        _links.erase(it);
    }
}
void Links::remove(const Point2D_u &p)
{
    while (true) {
        auto it
            = std::find_if(_links.begin(), _links.end(), [&p](const Link &s) {
                  return s._door_coord == p || s._diamond_coord == p;
              });
        if (it == _links.end())
            return;
        _links.erase(it);
    }
}

void Links::remove(const Point2D_u &diamond, const Point2D_u &door)
{
    while (true) {
        auto it
            = std::find_if(_links.begin(), _links.end(), [&diamond, &door](const Link &s) {
                  return s._door_coord == door && s._diamond_coord == diamond;
              });
        if (it == _links.end())
            return;
        _links.erase(it);
    }
}

std::list<const Diamond *> *Links::get(const Door *const d)
{
    std::list<const Diamond *> *list  = new std::list<const Diamond *>();
    std::vector<Link>::iterator begin = _links.begin();
    while (true) {
        auto it = std::find_if(
            begin, _links.end(), [&d](const Link &s) { return s._door == d; });
        if (it == _links.end())
            return list;
        list->push_back(it->_diamond);
        begin = it + 1;
    }
}

std::list<Door *> *Links::get(const Diamond *const d)
{
    std::list<Door *> *list = new std::list<Door *>();
    auto begin              = _links.begin();
    while (true) {
        std::vector<Link>::iterator it
            = std::find_if(begin, _links.end(), [&d](const Link &s) {
                  return s._diamond == d;
              });
        if (it == _links.end()) {
            return list;
        }
        list->push_back(it->_door);
        begin = it + 1;
    }
}

bool Links::exists(const Link &l)
{
    for (auto e : _links)
        if (e == l)
            return true;
    return false;
}

const std::vector<Link> Links::get_links() const { return _links; }