#ifndef INCLUDE_MODEL_LEVELLINKS_H_
#define INCLUDE_MODEL_LEVELLINKS_H_

#include <list>

#include "Util/Point2D.hpp"

struct SquareID {
    size_t _id;
    Point2D_u _coord;

    SquareID(const size_t id, const Point2D_u coord) : _id(id), _coord(coord) {}
    SquareID(const SquareID &d) : _id(d._id), _coord(d._coord) {}
};

inline bool operator==(const SquareID &a, const SquareID &b)
{
    return a._id == b._id && a._coord == b._coord;
}

struct LevelLink {
    SquareID _from; // Must be a Door
    SquareID _to;   // Can be any Accessible Square or Door

    LevelLink(const size_t from,
              const Point2D_u from_coord,
              const size_t to,
              const Point2D_u to_coord)
        : _from(from, from_coord), _to(to, to_coord)
    {
    }
    LevelLink(const LevelLink &l) : _from(l._from), _to(l._to) {}
};

class LevelLinks
{
private:
    std::list<LevelLink> _links;

    LevelLink &
    get_link(const size_t &id, const Point2D_u &coord, bool from = true);
    void _set(const size_t, const Point2D_u, const size_t, const Point2D_u);
    std::list<LevelLink>::iterator
    it_from(const size_t &id, const Point2D_u &coord, bool from = true);
    std::list<LevelLink>::iterator
    it_from(const size_t &id,
            const std::list<LevelLink>::iterator &begin,
            bool from = true);

public:
    void set(const size_t,
             const Point2D_u,
             const size_t,
             const Point2D_u,
             bool bothways = true);

    void remove_from(const size_t &id, const Point2D_u &coord);
    void remove_from(const size_t &id);
    void remove_to(const size_t &id, const Point2D_u &coord);
    void remove_to(const size_t &id);
    void remove(const size_t &id, const Point2D_u &coord);
    void remove(const size_t &id);

    void decrement_level_id(const size_t& index);

    bool has(const size_t &id, const Point2D_u &coord, bool from = true);
    const SquareID &get(const size_t &id, const Point2D_u &coord);
    const std::list<LevelLink> get_links() const;
};

#endif // !INCLUDE_MODEL_LEVELLINKS_H_
