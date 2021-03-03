#include "Model/AI/Algorithms/AStar.hpp"

#include <iostream>

void NodeBoard::reset()
{
    _board = _init; // deep copy
}

void NodeBoard::gen_init()
{
    for (int i = 0; i < dimensions().x(); i++) {
        _init.push_back(NodeVector());
        for (int j = 0; j < dimensions().y(); j++)
            _init[i].push_back(Node({i, j}));
    }
    print();
}

void NodeBoard::gen_init(const Board &b)
{
    gen_init();
    for (int i = 0; i < b.dimensions().x(); i++)
        for (int j = 0; j < b.dimensions().y(); j++)
            _init[i][j]._accessible = b.get_square(i, j)->is_accessible();
    print();
}

NodeBoard::NodeBoard(const size_t &x, const size_t &y) : Dimensional(x, y)
{
    _board = NodeVector2D();
    _init  = NodeVector2D();
    gen_init();
    _board = _init;
}
NodeBoard::NodeBoard(const Dimensions &p) : NodeBoard(p.x(), p.y()) {}
NodeBoard::NodeBoard(const Board &b) : Dimensional(b.dimensions())
{
    _board = NodeVector2D();
    _init  = NodeVector2D();
    gen_init(b);
    _board = _init;
}

Node &NodeBoard::get(const Point2D_u &p) { return _board[p.x()][p.y()]; }

const NodeDeque *
AStar::gen_path(const Point2D &start, const Point2D &current, NodeBoard &board)
{
    Point2D curr = current;
    _last_path->clear();
    do {
        _last_path->push_front(curr);
        if (!(board.get(curr)._parent.x() >= 0
              && board.get(curr)._parent.y() >= 0)) {
            _last_path->clear();
            _last_path->push_front(start);
            return _last_path;
        }
        curr = board.get(curr)._parent;
    } while (curr != start);
    return _last_path;
}

AStar::AStar(const Board *b)
{
    _board     = b;
    _last_path = new NodeDeque();
}
AStar::~AStar() { delete _last_path; }

#include <iostream>

const NodeDeque *AStar::path(const Point2D &start,
                             const Point2D &goal,
                             MoveSet *m,
                             Heuristic h_type)
{
    NodeBoard board(*_board);
    NodeQueue frontier;
    NodeVector closed;
    Node current;

    frontier.insert(board.get(start));

    while (!frontier.empty()) {
        // Pop
        current = frontier.pop();
        closed.push_back(current);

        const Point2D &curr = current._coord;

        // End condition
        if (curr == goal)
            return gen_path(start, curr, board);

        // Gen neighbours
        const std::vector<Point2D> &move_set
            = m->gen_move_set(&board, curr, false);

        // Process neighbours
        for (auto e : move_set) {
            if (!board.contains(e))
                continue;
            Node &n = board.get(e);

            if (std::find(closed.begin(), closed.end(), n) != closed.end())
                continue;
            if (frontier.contains(n))
                if (n._total_heuristic < current._total_heuristic + 1.0)
                    continue;
                else
                    frontier.erase(n);

            // Recalculate total heuristic for Node n
            n._cost = current._cost + 1;
            if (n._heuristic < 0)
                switch (h_type) {
                    case Heuristic::DIAGONAL:
                        n._heuristic = double(e.diagonal_distance(goal));
                        break;
                    case Heuristic::EUCLIDIAN:
                        n._heuristic = double(e.euclidian_distance(goal));
                        break;
                    case Heuristic::MIN_AXIS:
                        n._heuristic = double(e.min_axis_distance(goal));
                        break;
                    case Heuristic::MANHATTAN:
                        n._heuristic = double(e.manhattan_distance(goal));
                        break;
                }
            n._total_heuristic = n._cost + n._heuristic;
            n._parent          = curr;
            frontier.insert(n);
        }
    }

    _last_path->clear();
    _last_path->push_back(start);
    return _last_path;
}

void NodeBoard::print()
{
    for (auto line : _board) {
        for (auto e : line)
            std::cout << (e._accessible ? (e._heuristic < 0 ? "-" : "#") : "X");
            std::cout << std::endl;
    }
}
