#ifndef INCLUDE_MODEL_BOARD_HPP_
#define INCLUDE_MODEL_BOARD_HPP_

#include <random>
#include <vector>

#include "Controller/Input.hpp"
#include "Model/Board/Square.hpp"
#include "Model/Event/Event.hpp"
#include "Model/GameObject/GameObject.hpp"
#include "Util/Dimensional.hpp"
#include "Model/Board/Door.hpp"

enum class BoardSeekOption {
    ALL,
    ACCESSIBLE,
    DOOR,
    DIAMOND,
    NO_MONSTER,
    MONSTER,
    ACCESSIBLE_NO_MONSTER
};

class Board : public Dimensional
{
private:
    std::vector<std::vector<Square *>> _grid;
    Point2D_u _cursor;
    bool _show_cursor;

    const Point2D_u seek_LR(const Point2D_u &pos_init,
                            const bool go_right,
                            const BoardSeekOption &option) const;
    const Point2D_u seek_UD(const Point2D_u &pos_init,
                            const bool go_down,
                            const BoardSeekOption &option) const;
    bool seek_X(const Point2D_u &pos_init,
                Point2D_u &pos,
                const BoardSeekOption &option,
                bool last_out_of_bound) const;
    bool seek_Y(const Point2D_u &pos_init,
                Point2D_u &pos,
                const BoardSeekOption &option,
                bool last_out_of_bound) const;

    const Point2D_u seek_diag(const Point2D_u &pos_init,
                              const Input &input,
                              const BoardSeekOption &option) const;
    const Point2D_u seek_diag(const Point2D_u &pos_init,
                              Point2D &diff,
                              const Point2D &dir,
                              const BoardSeekOption &option) const;

    const bool seek_check(const Point2D_u &coord,
                          const BoardSeekOption &option) const;

public:
    explicit Board(std::vector<std::vector<Square *>>);
    explicit Board(const Board &);
    Board(const std::size_t &, const std::size_t &);
    Board(const Dimensions &);
    ~Board();

    // delete dimensions setters
    void set_dimensions(const Dimensions &d)                          = delete;
    void set_dimensions(const unsigned int &x, const unsigned int &y) = delete;

    const bool is_in_grid(const std::size_t &,
                          const std::size_t &) const; // Legacy
    const bool is_in_grid(const Point2D_u &) const;   // Legacy
    Square *get_square(const std::size_t &, const std::size_t &) const;
    Square *get_square(const Point2D_u &) const;
    void set_square(const std::size_t &, const std::size_t &, Square *);
    void set_square(const Point2D_u &, Square *);

    bool move_cursor(const Point2D_u &coord);
    const Point2D_u &cursor() const;

    const Point2D_u seek(const Point2D_u &pos,
                         const Input &direction,
                         const BoardSeekOption &option
                         = BoardSeekOption::ALL) const;

    void add_object(const GameObject *const o, const Point2D_u &coord);
    void add_object(const GameObject *const o,
                    const Point2D_u &coord,
                    BoardEventQueue &event_queue);
    void remove_object(const GameObject *const o, const Point2D_u &coord);

    void open_door(const Point2D_u &coord);
    void close_door(const Point2D_u &coord);

    const Point2D_u rand_coord(const BoardSeekOption &option
                               = BoardSeekOption::ALL) const;

    void show_cursor(bool show) { _show_cursor = show; }
    const bool show_cursor() const { return _show_cursor; }
};

#endif // INCLUDE_MODEL_BOARD_HPP_
