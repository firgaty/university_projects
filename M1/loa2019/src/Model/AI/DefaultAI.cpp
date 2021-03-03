#include "Model/AI/DefaultAI.hpp"


Point2D DefaultAI::move(const Point2D &coord,
                        const Point2D &goal,
                        const Board *board,
                        MoveSet *move_set)
{
    return AStar(board)
        .path(Point2D(coord), Point2D(goal), move_set, Heuristic::DIAGONAL)
        ->front()
        ._coord;
}