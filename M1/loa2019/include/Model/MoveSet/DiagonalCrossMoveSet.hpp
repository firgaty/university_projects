#ifndef INCLUDE_MOVESET_DIAGONALCROSSMOVESET_HPP_
#define INCLUDE_MOVESET_DIAGONALCROSSMOVESET_HPP_

#include "MoveSet.hpp"

class DiagonalCrossMoveSet : public virtual MoveSet
{
public:
    DiagonalCrossMoveSet() {}
    virtual const std::vector<Point2D>
    gen_move_set(Dimensional *board, Point2D coord, bool save = true);
    const MoveSetIDs getmsID() const {return MoveSetIDs::DIAGONAL_CROSS_MOVE;}
    virtual ~DiagonalCrossMoveSet() = default;
};

#endif // !INCLUDE_MOVESET_DIAGONALCROSSMOVESET_HPP_