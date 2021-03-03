#ifndef MODEL_AI_AI_HPP_
#define MODEL_AI_AI_HPP_

#include "Model/Board/Board.hpp"
#include "Model/MoveSet/MoveSet.hpp"
#include "Util/Point2D.hpp"

/**
 * @brief Abstract AI class.
 *
 */
class AI
{
public:
    virtual Point2D move(const Point2D &coord,
                         const Point2D &goal,
                         const Board *board,
                         MoveSet *move_set)
        = 0;
    ~AI() {}
    friend std::ostream &operator<<(std::ostream &os,const AI &ms);

};

#endif // !MODEL_AI_AI_HPP_
