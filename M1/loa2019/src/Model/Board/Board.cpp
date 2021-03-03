#include <iostream>
#include <string>

#include "Model/Board/Board.hpp"
#include "Model/Board/Door.hpp"

/**
 * @brief Construct a new Board:: Board object
 *
 * @param squares
 */
Board::Board(std::vector<std::vector<Square *>> squares) {} // TODO

/**
 * @brief Copy constructor of a Board object
 *
 * @param a
 */
Board::Board(Board const &a)
    : _cursor(Point2D_u()), _show_cursor(false), Dimensional(a.dimensions())
{
    _grid = std::vector<std::vector<Square *>>(a.x());
    for (std::size_t i(0); i < a.x(); i++) {
        _grid[i] = std::vector<Square *>(a.y());
        for (std::size_t j(0); j < a.y(); j++)
            _grid[i][j] = new Square(a.get_square(i, j));
    }
}

/**
 * @brief Construct a new Board object
 *
 * Creates a base grid of accessible Square
 *
 * @param x
 * @param y
 */
Board::Board(const std::size_t &x, const std::size_t &y)
    : _cursor(Point2D_u()), Dimensional(Dimensions(x, y))
{
    _grid = std::vector<std::vector<Square *>>(x);
    for (std::size_t i(0); i < x; i++) {
        _grid[i] = std::vector<Square *>(y);
        for (std::size_t j(0); j < y; j++)
            _grid[i][j] = new Square(true);
    }
}

Board::Board(const Dimensions &dimensions)
    : Board(dimensions.x(), dimensions.y())
{
}

Board::~Board()
{
    // Delete all pointers to Square instances.
    for (auto i : _grid)
        for (auto j : i)
            delete j;
}

const bool Board::is_in_grid(const std::size_t &x, const std::size_t &y) const
{
    return contains(x, y);
}

const bool Board::is_in_grid(const Point2D_u &coord) const
{
    return contains(coord);
}

Square *Board::get_square(const std::size_t &x, const std::size_t &y) const
{
    if (is_in_grid(x, y))
        return _grid[x][y];
    return nullptr;
}

Square *Board::get_square(const Point2D_u &coord) const
{
    if (is_in_grid(coord))
        return _grid[coord.x()][coord.y()];
    return nullptr;
}

void Board::set_square(const std::size_t &x, const std::size_t &y, Square *s)
{
    if (!is_in_grid(x, y))
        return;
    if ((_grid[x][y]))
        delete _grid[x][y];
    _grid[x][y] = s;
}

void Board::set_square(const Point2D_u &p, Square *s)
{
    set_square(p.x(), p.y(), s);
}

bool Board::move_cursor(const Point2D_u &coord)
{
    bool moved = false;
    if (coord != _cursor) {
        if (coord.x() < _dimensions.x()) {
            _cursor = Point2D_u(coord.x(), _cursor.y());
            moved   = true;
        }
        if (coord.y() < _dimensions.y()) {
            _cursor = Point2D_u(_cursor.x(), coord.y());
            moved   = true;
        }
    }
    return moved;
}

const Point2D_u &Board::cursor() const { return _cursor; }

void Board::add_object(const GameObject *const o, const Point2D_u &coord)
{
    Square *s;
    if ((s = get_square(coord)))
        s->add_object(o);
}

void Board::add_object(const GameObject *const o,
                       const Point2D_u &coord,
                       BoardEventQueue &event_queue)
{
    Square *s;
    if (!(s = get_square(coord)))
        return;
    if (!s->is_empty()) {
        event_queue.push_back({BoardEventType::OBJECT, coord, o});
    }
    if (Door::is_this_type(s)) {
        event_queue.push_back({BoardEventType::DOOR, coord, o});
    }
    s->add_object(o);
}
void Board::remove_object(const GameObject *const o, const Point2D_u &coord)
{
    Square *s;
    if ((s = get_square(coord)))
        s->remove_object(o);
}

void Board::open_door(const Point2D_u &coord)
{
    Square *s;
    if ((s = get_square(coord)) && Door::is_this_type(s)) {
        dynamic_cast<Door *>(s)->open();
    }
}

void Board::close_door(const Point2D_u &coord)
{
    Square *s;
    if ((s = get_square(coord)) && Door::is_this_type(s)) {
        dynamic_cast<Door *>(s)->close();
    }
}

/**
 * @brief Seeks a Square respecting the option in the direction of the input
 * from the initial pos
 *
 * @param pos
 * @param direction
 * @param option
 * @return const Point2D_u pos if the seek failed.
 */
const Point2D_u Board::seek(const Point2D_u &pos,
                            const Input &direction,
                            const BoardSeekOption &option) const
{
    if (direction == UP_LEFT || direction == UP_RIGHT || direction == DOWN_LEFT
        || direction == DOWN_LEFT)
        return seek_diag(pos, direction, option);
    switch (direction) {
        case UP: return seek_UD(pos, false, option);
        case DOWN: return seek_UD(pos, true, option);
        case RIGHT: return seek_LR(pos, true, option);
        case LEFT: return seek_LR(pos, false, option);
        default: return pos;
    }
}

const bool Board::seek_check(const Point2D_u &coord,
                             const BoardSeekOption &option) const
{
    Square *s;
    if (!(s = get_square(coord)))
        return false;

    auto has_monster = [](Square *s) -> bool {
        for (int i = 0; i < s->size(); i++)
            if (s->get(i)->game_object_type() == GameObjectType::MONSTER)
                return true;
        return false;
    };

    switch (option) {
        case BoardSeekOption::ALL: return true; break;
        case BoardSeekOption::ACCESSIBLE: return s->is_accessible(); break;
        case BoardSeekOption::DOOR: return Door::is_this_type(s); break;
        case BoardSeekOption::DIAMOND:
            return !s->is_empty()
                   && s->get(0)->game_object_type() == GameObjectType::DIAMOND;
            break;
        case BoardSeekOption::NO_MONSTER:
            return s->is_empty() || !has_monster(s);
            break;
        case BoardSeekOption::ACCESSIBLE_NO_MONSTER:
            return s->is_accessible() && s->is_empty() || !has_monster(s);
            break;
        case BoardSeekOption::MONSTER:
            return !(s->is_empty() || !has_monster(s));
            break;
    }
    return false;
}

const Point2D_u Board::seek_LR(const Point2D_u &pos_init,
                               bool go_right,
                               const BoardSeekOption &option) const
{
    Point2D_u dir(0, go_right ? 1 : -1);
    Point2D_u out;

    for (Point2D_u pos(pos_init + dir); is_in_grid(pos);
         pos += dir, out = pos) {
        if (seek_X(pos, out, option, false))
            return out;
    }
    return pos_init;
}

/**
 * @brief Seeks the first square that fist it's option
 *
 * in this order:
 *
 * 5
 * 3
 * 1
 * 0
 * 2
 * 4
 * 6
 *
 * @param pos_init
 * @param pos
 * @param option
 * @param last_out_of_bound
 * @return true
 * @return false
 */
bool Board::seek_X(const Point2D_u &pos_init,
                   Point2D_u &pos,
                   const BoardSeekOption &option,
                   bool last_out_of_bound) const
{
    if (seek_check(pos, option))
        return true;
    std::cout << pos << pos_init << std::endl;
    if (!(get_square(pos)))
        if (last_out_of_bound)
            return false;
        else
            last_out_of_bound = true;

    int diff = (pos - pos_init).x();
    if (diff < 0)
        pos = pos_init - Point2D_u(diff, 0);
    else
        pos = pos_init + Point2D_u(diff + 1, 0);

    return seek_X(pos_init, pos, option, last_out_of_bound);
}

const Point2D_u Board::seek_UD(const Point2D_u &pos_init,
                               const bool go_down,
                               const BoardSeekOption &option) const
{
    Point2D_u dir(go_down ? 1 : -1, 0);
    Point2D_u out;

    for (Point2D_u pos(pos_init + dir); is_in_grid(pos);
         pos += dir, out = pos) {
        out = pos;
        if (seek_Y(pos, out, option, false))
            return out;
    }
    return pos_init;
}

bool Board::seek_Y(const Point2D_u &pos_init,
                   Point2D_u &pos,
                   const BoardSeekOption &option,
                   bool last_out_of_bound) const
{
    std::cout << pos << std::endl;
    if (seek_check(pos, option))
        return true;

    if (!(get_square(pos)))
        if (last_out_of_bound)
            return false;
        else
            last_out_of_bound = true;

    int diff = (pos - pos_init).y();
    if (diff < 0)
        pos = pos_init - Point2D_u(0, diff);
    else
        pos = pos_init + Point2D_u(0, diff + 1);

    return seek_Y(pos_init, pos, option, last_out_of_bound);
}
const Point2D_u Board::seek_diag(const Point2D_u &pos_init,
                                 const Input &input,
                                 const BoardSeekOption &option) const
{
    Point2D dir, diff;
    switch (input) {
        case UP_RIGHT: dir = {-1, 1}; break;
        case UP_LEFT: dir = {-1, -1}; break;
        case DOWN_RIGHT: dir = {1, 1}; break;
        case DOWN_LEFT: dir = {1, -1}; break;
        default: return pos_init;
    }
    return seek_diag(pos_init, diff, dir, option);
}

const Point2D_u Board::seek_diag(const Point2D_u &pos_init,
                                 Point2D &diff,
                                 const Point2D &dir,
                                 const BoardSeekOption &option) const
{
    Point2D_u pos(pos_init + Point2D_u(diff * dir));
    if (seek_check(pos, option))
        return pos;

    // Out of bound
    if (pos.x() > _dimensions.x() && pos.y() > _dimensions.y())
        return pos_init;

    /**
     * (x, y) = | (0, y + 1)    if x == y
     *          | (y, x)        if x < y
     *          | (y + 1, x)    else
     */
    if (diff.x() == diff.y())
        diff = {0, diff.y() + 1};
    else if (diff.x() < diff.y())
        diff = {diff.y(), diff.x()};
    else
        diff = {diff.y() + 1, diff.x()};

    return seek_diag(pos_init, diff, dir, option);
}

const Point2D_u Board::rand_coord(const BoardSeekOption &option) const
{
    static std::default_random_engine gen;
    std::uniform_int_distribution<uint> distrib_x(0, _dimensions.x() - 1);
    std::uniform_int_distribution<uint> distrib_y(0, _dimensions.y() - 1);

    Point2D_u coord;

    do {
        coord = {distrib_x(gen), distrib_y(gen)};
    } while (!seek_check(coord, option));

    return coord;
}
