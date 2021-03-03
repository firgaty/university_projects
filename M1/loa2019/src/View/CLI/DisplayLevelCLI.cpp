#include "View/CLI/DisplayLevelCLI.hpp"

DisplayLevelCLI::DisplayLevelCLI()
{
    _dimensions = Dimensions();
    _board      = new DisplayBoardCLI();
}
DisplayLevelCLI::DisplayLevelCLI(Level *level) : DisplayLevelCLI()
{
    set_level(level);
}
DisplayLevelCLI::~DisplayLevelCLI() { delete _board; }

void DisplayLevelCLI::set_level(Level *level)
{
    if (level == nullptr || level == _level)
        return;
    set_state_fetched();

    _level = level;
    _string_array.reserve(_level->board()->width());

    if (height() < _level->board()->height())
        set_dimensions(_level->board()->height(), width());
    if (width() < _level->board()->width())
        set_dimensions(height(), _level->board()->width());

    for (int i = 0; i < height(); i++)
        _string_array.push_back(std::u32string(width(), ' '));
    set_state_fetched();
}

void DisplayLevelCLI::gen_string_array()
{
    if (_state == DisplayState::GENERATED)
        return;
    if (!(_level))
        return;
    _board->set_board(_level->board());

    Point2D_u board_origin(0, 0);
    repaint(board_origin, *_board);

    if (_level->state() == LevelState::SELECT) {
        Point2D_u cursor = _level->board()->cursor();
        _string_array[board_origin.x() + cursor.x()]
                     [board_origin.y() + cursor.y()]
            = char_from_color(Color::CURSOR);
    }
    set_state_generated();
}