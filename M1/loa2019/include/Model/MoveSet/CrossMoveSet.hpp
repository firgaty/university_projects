#ifndef INCLUDE_MOVESET_CROSSMOVESET_HPP_
#define INCLUDE_MOVESET_CROSSMOVESET_HPP_

#include "MoveSet.hpp"

class CrossMoveSet : public virtual MoveSet
{
public:
    CrossMoveSet() {}
    virtual const std::vector<Point2D>
    gen_move_set(Dimensional *board, Point2D coord, bool save = true);
    const MoveSetIDs getmsID() const {return MoveSetIDs::CROSS_MOVE;}
    virtual ~CrossMoveSet() = default;
};

#endif // !INCLUDE_MOVESET_CROSSMOVESET_HPP_