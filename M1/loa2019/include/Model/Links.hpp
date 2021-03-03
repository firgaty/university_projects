#ifndef INCLUDE_LINKS_HPP_
#define INCLUDE_LINKS_HPP_

#include <list>
#include <ostream>
#include <vector>

#include "GameObject/Diamond.hpp"
#include "Model/Board/Door.hpp"
#include "Util/Point2D.hpp"

struct Link {
    const Diamond *_diamond;
    Point2D_u _diamond_coord;
    Door *_door;
    Point2D_u _door_coord;

    friend std::ostream &operator<<(std::ostream &os, const Link &a)
    {
        os << "[ " << a._diamond_coord << " : " << a._door_coord << " ]";
        return os;
    }
};

inline bool operator==(const Link &a, const Link &b)
{
    return a._diamond == b._diamond && a._door == b._door;
}
inline bool operator!=(const Link &a, const Link &b) { return !(a == b); }

class Links
{
private:
    mutable std::vector<Link> _links;

public:
    Links();
    ~Links();

    void add(const Link l);
    void add(const Diamond *, const Point2D_u, Door *, const Point2D_u);
    void remove(const Diamond *const d);
    void remove(const Door *const d);
    void remove(const Point2D_u &coord);
    void remove(const Point2D_u &diamond, const Point2D_u &door);

    const std::vector<Link> get_links() const;

    std::list<const Diamond *> *get(const Door *const d);
    std::list<Door *> *get(const Diamond *const d);

    bool exists(const Link &l);

    friend std::ostream &operator<<(std::ostream &os, const Links &a)
    {
        for (Link l : a._links)
            os << l << std::endl;
        return os;
    }
};

// std::ostream &operator<<(std::ostream &os, const Link &a)

// std::ostream &operator<<(std::ostream &os, const Links &a)

#endif // ! INCLUDE_LINKS_HPP_