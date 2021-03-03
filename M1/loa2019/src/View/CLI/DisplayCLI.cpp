#include "View/CLI/DisplayCLI.hpp"

char DisplayCLI::char_from_color(const Color &c) const
{
    switch (c) {
        case Color::EMPTY: return ' ';
        case Color::WALL1: return 'H';
        case Color::WALL2: return 'X';
        case Color::DOOR_CLOSE: return '+';
        case Color::DOOR_OPEN: return '-';
        case Color::DOOR_GOAL_CLOSE: return 'x';
        case Color::DOOR_GOAL_OPEN: return 'o';
        case Color::MON1: return 'm';
        case Color::MON2: return 'M';
        case Color::MON3: return 'n';
        case Color::MON4: return 'N';
        case Color::DIAMS: return '$';
        case Color::PLAYER: return 'c';
        case Color::CHARG1: return '*';
        case Color::CHARG2: return '%';
        case Color::CHARG3: return '@';
        case Color::CURSOR: return '!';
    }
    return 'E';
}

void DisplayCLI::display()
{
    for (std::u32string s : _string_array)
        std::cout << Convert::to_utf8(s) << std::endl;
    set_state_fetched();
}
const StringArray &DisplayCLI::get_string_array()
{
    set_state_fetched();
    return _string_array;
}

bool DisplayCLI::repaint(const Point2D_u &origin, DisplayCLI &paint)
{
    if (origin.x() + paint.height() > _dimensions.x()
        || origin.y() + paint.width() > _dimensions.y())
        return false;

    paint.gen_string_array();
    StringArray array = paint.get_string_array();

    for (int i = origin.x(); i < height() && i < origin.x() + paint.height();
         i++) {
        repaint_line(i, origin.y(), array[i - origin.x()]);
    }
    return true;
}

bool DisplayCLI::repaint_line(const size_t &line,
                              const size_t &begin,
                              const std::u32string &paint)
{
    const size_t length = paint.size();

    if (begin + length > _dimensions.y()) {
        std::cout << begin + length << " out of Y bound " << _dimensions.y()
                  << std::endl;
        return false;
    }
    if (line > _dimensions.x()) {
        std::cout << line << " out of X bound " << _dimensions.y() << std::endl;
        return false;
    }

    if (begin == 0 && length == _dimensions.y()) {
        _string_array[line] = paint;
        return true;
    }

    for (int i = begin; i < begin + length; i++) {
        _string_array[line][i] = paint[i - begin];
    }
    return true;
}

void DisplayCLI::set_state_fetched() { _state = DisplayState::FETCHED; }
void DisplayCLI::set_state_generated() { _state = DisplayState::GENERATED; }