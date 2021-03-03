#ifndef INCLUDE_MOVESET_SQUAREMOVESET_HPP_
#define INCLUDE_MOVESET_SQUAREMOVESET_HPP_

#include <algorithm>

#include "CrossMoveSet.hpp"
#include "DiagonalCrossMoveSet.hpp"

class SquareMoveSet : public virtual CrossMoveSet,
                      public virtual DiagonalCrossMoveSet
{
public:
    SquareMoveSet() {}
    virtual const std::vector<Point2D>
    gen_move_set(Dimensional *board, Point2D coord, bool save = true);
    const MoveSetIDs getmsID() const {return MoveSetIDs::SQUARE;}
    virtual ~SquareMoveSet() = default;
};

#endif // !INCLUDE_MOVESET_SQUAREMOVESET_HPP_