#ifndef INCLUDE_MODEL_BOARDCONTAINER_HPP_
#define INCLUDE_MODEL_BOARDCONTAINER_HPP_

#include "Controller/Input.hpp"
#include "Model/Board/Board.hpp"

class BoardContainer
{
protected:
    Board *_board;

    BoardContainer(Board *board = nullptr) : _board(board) {}

public:
    ~BoardContainer()
    {
        if ((_board))
            delete _board;
    }

    bool move_cursor(const Input &input, const BoardSeekOption &option)
    {
        /*
         *   Board is layed out like this:
         *   .__________y
         *   |
         *   |
         *   |
         *   |
         *   x
         */
        if (option == BoardSeekOption::ALL)
            return move_cursor(
                pos_from_input(input, Point2D_u(_board->cursor())));
        return move_cursor(_board->seek(_board->cursor(), input, option));
    }

    bool move_cursor(const Point2D_u &coord)
    {
        return _board->move_cursor(coord);
    }

    Point2D_u pos_from_input(const Input &input, Point2D_u pos) const
    {
        if (input & Input::UP) {
            pos -= Point2D_u{1, 0};
        }
        if (input & Input::DOWN) {
            pos += Point2D_u{1, 0};
        }
        if (input & Input::LEFT) {
            pos -= Point2D_u{0, 1};
        }
        if (input & Input::RIGHT) {
            pos += Point2D_u{0, 1};
        }
        return pos;
    }

    Board *board() const { return _board; }

    void set_board(Board *board, bool del = true)
    {
        if (_board != nullptr && del)
            delete _board;
        _board = board;
    }
};

#endif