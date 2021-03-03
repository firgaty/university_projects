#ifndef MODEL_AI_ALGORITHMS_ASTAR_HPP_
#define MODEL_AI_ALGORITHMS_ASTAR_HPP_

#include <algorithm>
#include <deque>
#include <set>
#include <vector>

#include "Model/Board/Board.hpp"
#include "Model/MoveSet/MoveSet.hpp"
#include "Util/Dimensional.hpp"
#include "Model/AI/Algorithms/PriorityQueue.hpp"

struct Node {
    Point2D _coord          = Point2D();
    Point2D _parent         = Point2D(-1, -1);
    bool _accessible        = true;
    double _heuristic       = -1.0;
    double _cost            = 0.0;
    double _total_heuristic = 0.0;

    Node()
    {
        _coord           = Point2D();
        _parent          = Point2D(-1, -1);
        _accessible      = true;
        _heuristic       = -1;
        _cost            = 0;
        _total_heuristic = 0;
    }
    Node(const Point2D coord) : Node() { _coord = coord; }
    Node(const Point2D coord, bool accessible) : Node(coord)
    {
        _accessible = accessible;
    }
};

inline bool operator==(const Node &a, const Node &b)
{
    return a._coord == b._coord;
}
inline bool operator<(const Node &a, const Node &b)
{
    return a._total_heuristic + a._cost < b._total_heuristic + b._cost;
}

// Functor
struct NodeCompare {
    bool operator()(const Node &a, const Node &b)
    {
        return a._total_heuristic + a._cost < b._total_heuristic + b._cost;
    }
};

using NodeVector   = std::vector<Node>;
using NodeVector2D = std::vector<NodeVector>;

class NodeBoard : public virtual Dimensional
{
private:
    NodeVector2D _board;
    NodeVector2D _init;

    void reset();
    void gen_init();
    void gen_init(const Board &b);

public:
    NodeBoard(const size_t &x, const size_t &y);
    NodeBoard(const Dimensions &p);
    NodeBoard(const Board &b);

    Node &get(const Point2D_u &p);

    // TODO: delete
    void print();
};

using NodeDeque = std::deque<Node>;

using NodeQueue = PriorityQueue<Node, NodeDeque ,NodeCompare>;

enum class Heuristic { EUCLIDIAN, DIAGONAL, MIN_AXIS, MANHATTAN };

class AStar
{
protected:
    const Board *_board;
    NodeDeque *_last_path;

    const NodeDeque *
    gen_path(const Point2D &start, const Point2D &current, NodeBoard &board);

public:
    AStar(const Board *b);
    ~AStar();

    const NodeDeque *path(const Point2D &start,
                          const Point2D &goal,
                          MoveSet *m,
                          Heuristic h_type = Heuristic::DIAGONAL);
};

#endif // !MODEL_AI_ALGORITHMS_ASTAR_HPP_