#include "Model/Board/Door.hpp"
#include "View/CLI/DisplayBoardCLI.hpp"

DisplayBoardCLI::DisplayBoardCLI()
{
    _dimensions   = Dimensions();
    _string_array = StringArray();
}

DisplayBoardCLI::DisplayBoardCLI(const Board *board) : DisplayBoardCLI()
{
    set_board(board);
}

void DisplayBoardCLI::set_board(const Board *board)
{
    if (board == nullptr || board == _board)
        return;

    _dimensions = Dimensions(board->dimensions());

    _board = board;
    _string_array.reserve(height());

    _string_array = BlankCLI(_dimensions).get_string_array();

    set_state_fetched();
}

void DisplayBoardCLI::gen_string_array()
{

    if (_state == DisplayState::GENERATED)
        return;
    if (!(_board))
        return;

    Square *square        = nullptr;
    const GameObject *obj = nullptr;

    for (int i = 0; i < _dimensions.x(); i++) {
        std::u32string str = U"";
        for (int j = 0; j < _dimensions.y(); j++) {
            square = _board->get_square(i, j);
            if ((obj = square->get_last())) // Verify if has object
                str.push_back(char_from_color(obj->color()));
            else
                str.push_back(char_from_color(square->color()));
        }
        repaint_line(i, 0, str);
    }

    if (_board->show_cursor()) {
        Point2D_u cursor                      = _board->cursor();
        _string_array[cursor.x()][cursor.y()] = char_from_color(Color::CURSOR);
    }
    // set_state_generated();
}