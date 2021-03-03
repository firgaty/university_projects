#ifndef INCLUDE_MOVESET_MOVESET_HPP_
#define INCLUDE_MOVESET_MOVESET_HPP_

#include <vector>

#include "Util/Dimensional.hpp"
#include "Util/Point2D.hpp"
#include "MoveSetIDs.hpp"

/**
 * @brief Base abstract class to generate moves.
 *
 */
class MoveSet
{
protected:
    std::vector<Point2D> _move_set;

    MoveSet() {}

public:
    const std::vector<Point2D> get_move_set() const { return _move_set; }
    virtual const std::vector<Point2D>
    gen_move_set(Dimensional *board, Point2D coord, bool save = true) = 0;
    virtual ~MoveSet() { _move_set.~vector(); }
    virtual const MoveSetIDs getmsID() const {return MoveSetIDs::SQUARE;}
    friend std::ostream &operator<<(std::ostream &os,const MoveSet &ms);
};

#endif // INCLUDE_MOVESET_MOVESET_HPP_
