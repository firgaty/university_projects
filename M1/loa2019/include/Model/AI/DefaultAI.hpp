#ifndef MODEL_AI_DEFAULTAI_HPP_
#define MODEL_AI_DEFAULTAI_HPP_

#include "Model/AI/AI.hpp"
#include "Model/AI/Algorithms/AStar.hpp"
#include "Util/Point2D.hpp"

class DefaultAI : public virtual AI
{
public:
    Point2D move(const Point2D &coord,
                 const Point2D &goal,
                 const Board *board,
                 MoveSet *move_set);
};

#endif // !MODEL_AI_DEFAULTAI_HPP_