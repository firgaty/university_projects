#include "Model/MoveSet/CrossMoveSet.hpp"
#include "Model/MoveSet/DiagonalCrossMoveSet.hpp"
#include "Model/MoveSet/MoveSet.hpp"
#include "Model/MoveSet/MoveSetIDs.hpp"
#include "Model/MoveSet/SquareMoveSet.hpp"

const std::vector<Point2D>
DiagonalCrossMoveSet::gen_move_set(Dimensional *board, Point2D coord, bool save)
{
    _move_set.clear();
    std::vector<Point2D> move_set = std::vector<Point2D>();
    move_set.reserve(5);
    move_set.push_back(coord);
    if (board->contains(coord + Point2D(1, 1)))
        move_set.push_back(coord + Point2D(1, 1));
    if (board->contains(coord + Point2D(1, -1)))
        move_set.push_back(coord + Point2D(1, -1));
    if (board->contains(coord + Point2D(-1, 1)))
        move_set.push_back(coord + Point2D(-1, 1));
    if (board->contains(coord + Point2D(-1, -1)))
        move_set.push_back(coord + Point2D(-1, -1));
    if (save)
        _move_set = move_set;
    return move_set;
}


const std::vector<Point2D>
CrossMoveSet::gen_move_set(Dimensional *board, Point2D coord, bool save)
{
    _move_set.clear();
    std::vector<Point2D> move_set = std::vector<Point2D>();
    move_set.reserve(5);

    move_set.push_back(coord);
    if (board->contains(coord + Point2D(0, 1)))
        move_set.push_back(coord + Point2D(0, 1));
    if (board->contains(coord + Point2D(1, 0)))
        move_set.push_back(coord + Point2D(1, 0));
    if (board->contains(coord + Point2D(0, -1)))
        move_set.push_back(coord + Point2D(0, -1));
    if (board->contains(coord + Point2D(-1, 0)))
        move_set.push_back(coord + Point2D(-1, 0));
    if (save)
        _move_set = move_set;
    return move_set;
}


const std::vector<Point2D>
SquareMoveSet::gen_move_set(Dimensional *board, Point2D coord, bool save)
{
    std::vector<Point2D> strait
        = CrossMoveSet::gen_move_set(board, coord, false);
    std::vector<Point2D> diag
        = DiagonalCrossMoveSet::gen_move_set(board, coord, false);

    std::vector<Point2D> move_set = std::vector<Point2D>();
    move_set.reserve(strait.size() + diag.size());
    for(auto e : strait)
        move_set.push_back(e);
    for (Point2D elem : diag)
        if (std::find(move_set.begin(), move_set.end(), elem) == move_set.end())
            move_set.push_back(elem);

    if (save)
        _move_set = move_set;
    return move_set;
}
