#include <iostream>

#include "Model/Level.hpp"

Level::Level()
    : _board(nullptr),
      _player_state(PlayerObjectState(nullptr, Point2D_u(-1, -1), false)),
      _state(LevelState::PLAY)
{
    _monster_states = MonsterObjectStateVector();
    _diamond_states = DiamondObjectStateVector();
    _charger_states = ChargerObjectStateVector();
    _player_state   = PlayerObjectState(nullptr, Point2D_u());
    _links          = Links();
}

Level::~Level()
{
    delete _board;
    if ((_player_state._object))
        delete _player_state._object;
}

void Level::set_board(Board *board)
{
    if (_board != nullptr)
        delete _board;
    _board = board;
}
bool Level::set_monster(Monster *monster,
                        Point2D_u coord,
                        Point2D_u coord_init,
                        bool on_board)
{
    if (!_board->is_in_grid(coord))
        return false;
    _monster_states.add(
        MonsterObjectState{monster, coord, coord_init, on_board});
    if (on_board)
        _board->add_object(monster, coord);
    return true;
}
bool Level::set_diamond(Diamond *diamond,
                        Point2D_u coord,
                        Point2D_u coord_init,
                        bool on_board)
{
    if (!_board->is_in_grid(coord))
        return false;
    _diamond_states.add(
        DiamondObjectState{diamond, coord, coord_init, on_board});
    if (on_board)
        _board->add_object(diamond, coord);
    return true;
}
bool Level::set_charger(Charger *charger,
                        Point2D_u coord,
                        Point2D_u coord_init,
                        bool on_board)
{
    if (!_board->is_in_grid(coord))
        return false;
    _charger_states.add(
        ChargeObjectState{charger, coord, coord_init, on_board});
    if (on_board)
        _board->add_object(charger, coord);
    return true;
}

bool Level::set_monster(Monster *monster, Point2D_u coord, bool on_board)
{
    return set_monster(monster, coord, coord, on_board);
}
bool Level::set_diamond(Diamond *diamond, Point2D_u coord, bool on_board)
{
    return set_diamond(diamond, coord, coord, on_board);
}
bool Level::set_charger(Charger *charger, Point2D_u coord, bool on_board)
{
    return set_charger(charger, coord, coord, on_board);
}

bool Level::set_player(Point2D_u coord)
{
    if ((_player_state._object)) // If player already exists.
        return move_player(coord);

    if (!_board->is_in_grid(coord)
        || !_board->get_square(coord)->is_accessible())
        return false;

    _player_state._object = new Player();
    _player_state._coord  = coord;
    _board->add_object(_player_state._object, coord);

    return true;
}

bool Level::set_monster(Monster *monster)
{
    return set_monster(monster, _board->cursor(), true);
}
bool Level::set_diamond(Diamond *diamond)
{
    return set_diamond(diamond, _board->cursor(), true);
}
bool Level::set_charger(Charger *charger)
{
    return set_charger(charger, _board->cursor(), true);
}
bool Level::set_player() { return set_player(_board->cursor()); }

bool Level::set_link(Point2D_u diamond_coord, Point2D_u door_coord)
{
    Square *ds;
    Square *door;

    // Check if squares exist
    if (!((ds = _board->get_square(diamond_coord))
          && (door = _board->get_square(door_coord)))) {
        std::cout << "Error: square not in range" << std::endl;
        return false;
    }
    // Same with diamond
    if (!_diamond_states.has(diamond_coord)) {
        std::cout << "Error : diamond not found" << std::endl;
        return false;
    }
    // Check if door square is a door
    if (!Door::is_this_type(door)) {
        std::cout << "Error : door not found" << std::endl;
        return false;
    }

    Door *door2 = dynamic_cast<Door *>(door);

    door2->color();

    // Start link creation
    Diamond *d = _diamond_states.get(diamond_coord)._object;
    _links.add(d, diamond_coord, door2, door_coord);
    std::cout << _links << std::endl;
    return true;
}

#include <iostream>

Point2D_u Level::pos_from_input(const Input &input, Point2D_u pos) const
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
bool Level::move_player(const Input &input)
{
    Point2D_u pos(_player_state._coord);

    return move_player(pos_from_input(input, pos));
}
bool Level::move_player(const Point2D_u &coord)
{
    if (!_board->is_in_grid(coord)
        || !move_moveable(_player_state._object, _player_state._coord, coord))
        return false;
    _player_state._coord = coord;
    return true;
}

bool Level::move_cursor(const Input &input, const BoardSeekOption &option)
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
        return move_cursor(pos_from_input(input, Point2D_u(_board->cursor())));
    return move_cursor(_board->seek(_board->cursor(), input, option));
}

bool Level::move_cursor(const Point2D_u &coord)
{
    return _board->move_cursor(coord);
}
bool Level::move_monsters()
{
    for (int i = 0; i < _monster_states.size(); i++) {

        MonsterObjectState &o = _monster_states.get(i);
        Point2D_u to          = o._object->move(
            Point2D(o._coord), Point2D(_player_state._coord), _board);
        if (!move_monster(o, to))
            return false;
    }
    return true;
}
bool Level::move_moveable(const Moveable *m,
                          const Point2D_u &from,
                          const Point2D_u &to)
{
    if (!_board->is_in_grid(to) || !_board->get_square(to)->is_accessible())
        return false;
    _board->remove_object(m, from);
    _board->add_object(m, to, _events);
    return true;
}
bool Level::move_monster(MonsterObjectState &state, const Point2D_u &to)
{
    if (!state._state || !move_moveable(state._object, state._coord, to)) {
        return false;
    }
    state._coord = to;
    return true;
}

const LevelState &Level::state() const { return _state; }
void Level::set_state_play() { _state = LevelState::PLAY; }
void Level::set_state_select()
{
    _state = LevelState::SELECT;
    _board->move_cursor(_player_state._coord);
}

const Board *Level::board() const { return _board; }

ActionOutput Level::internal_act_on_input(const Input &input)
{
    switch (_state) {
        case LevelState::PLAY:
            return play_turn(input) ? ACTION_SUCCESS : ACTION_FAILED;
        case LevelState::SELECT:
            return move_cursor(input) ? ACTION_SUCCESS : ACTION_FAILED;
    }
    return ACTION_FAILED;
}

ActionOutput Level::on_actionable_element_exit() { return ACTION_FAILED; }

const std::vector<MonsterObjectState> &Level::monster_states() const
{
    return _monster_states.get_vector();
}
const std::vector<DiamondObjectState> &Level::diamond_states() const
{
    return _diamond_states.get_vector();
}
const std::vector<ChargerObjectState> &Level::charger_states() const
{
    return _charger_states.get_vector();
}
const PlayerObjectState &Level::player_state() const { return _player_state; }

bool Level::play_turn(const Input &input)
{
    _events.flush();
    bool moved = move_player(input);
    if (!moved)
        return false;
    move_monsters();
    resolve_events();
    return true;
}

void Level::resolve_events()
{
    while (!_events.empty()) {
        BoardEvent e = _events.pop_front(); // TODO: test
        switch (e._type) {
            case BoardEventType::OBJECT: resolve_object_event(e); break;
            case BoardEventType::DOOR: resolve_door_event(e); break;
            default: break;
        }
    }
}

void Level::resolve_object_event(const BoardEvent &e)
{
    /* Let, P, M and C represent Player, Monster, and Collectible, the
     * configurations are the following:
     *    1 2 3 4 5 6
     * 2:   P M
     * 1: P M M M P M
     * 0: C C C P M M
     *
     * Collectibles are Charger and Diamond objects.
     */
    if (e._type != BoardEventType::OBJECT)
        return;
    Square *s = nullptr;
    if (!(s = _board->get_square(e._coord)) || s->size() < 2)
        return;

    const GameObject *obj0, *obj1, *obj2;
    obj1 = s->get(1);
    obj0 = s->get(0);
    if (Player::is_this_type(obj1)) {
        if (Diamond::is_this_type(obj0)) { // Case 1
            resolve_door_link(dynamic_cast<const Diamond *>(obj0));
            remove_from_board(obj0);

            add_level_event({LevelEventType::DIAMOND, LevelEventBody()});
            if (_diamond_states.all_states_false())
                add_level_event(
                    {LevelEventType::NO_DIAMONDS, LevelEventBody()});
            return;
        }
        if (Charger::is_this_type(obj0)) { // Case 1
            remove_from_board(obj0);

            add_level_event(
                {LevelEventType::CHARGER,
                 LevelEventBody(
                     dynamic_cast<const Charger *>(obj0)->get_type())});
            if (_charger_states.all_states_false())
                add_level_event({LevelEventType::NO_CHARGER, LevelEventBody()});
            return;
        }
        if (Monster::is_this_type(obj0)) { // Case 5

            add_level_event({LevelEventType::LOSE, LevelEventBody()});
            return;
        }
    }
    if (Monster::is_this_type(obj1)) {
        if (Monster::is_this_type(obj0)) { // Case 6
            remove_from_board(obj0);
            remove_from_board(obj1);
            if (_monster_states.all_states_false())
                add_level_event({LevelEventType::NO_MONSTER, LevelEventBody()});
            return;
        }
        if (Player::is_this_type(obj0)) { // Case 4
            add_level_event({LevelEventType::LOSE, LevelEventBody()});
            return;
        }
        if (s->size() >= 2) {
            obj2 = s->get(2);
            if (Player::is_this_type(obj2)) { // Case 2
                add_level_event({LevelEventType::LOSE, LevelEventBody()});
                return;
            }
            if (Monster::is_this_type(obj2)) { // Case 3
                remove_from_board(obj2);
                remove_from_board(obj1);
                if (_monster_states.all_states_false())
                    add_level_event(
                        {LevelEventType::NO_MONSTER, LevelEventBody()});
                return;
            }
        }
    }
}

void Level::resolve_door_event(const BoardEvent &e)
{
    if (e._type != BoardEventType::DOOR)
        return;
    if (!Door::is_this_type(_board->get_square(_player_state._coord)))
        return;
    add_level_event(
        {LevelEventType::DOOR, LevelEventBody(_player_state._coord)});
}

void Level::resolve_door_link(const Diamond *d)
{
    auto l = _links.get(d);
    Door *door;
    int i = 0;
    while ((door = l->front())) {
        std::cout << i << std::endl;
        door->open();
        l->pop_front();
    }
}

void Level::remove_from_board(const GameObject *o)
{
    Point2D_u p;
    if (Diamond::is_this_type(o)) {
        DiamondObjectState s = _diamond_states.get(o);
        s._state             = false;
        p                    = s._coord;
    } else if (Charger::is_this_type(o)) {
        ChargeObjectState s = _charger_states.get(o);
        s._state            = false;
        p                   = s._coord;
    } else if (Monster::is_this_type(o)) {
        MonsterObjectState s = _monster_states.get(o);
        s._state             = false;
        p                    = s._coord;
    } else
        return;
    _board->remove_object(o, p);
}

void Level::add_level_event(const LevelEvent e)
{
    if ((_level_events))
        _level_events->push_back(e);
}

bool Level::set_level_event_queue(LevelEventQueue *queue)
{
    if ((queue)) {
        _level_events = queue;
        return true;
    }
    return false;
}

bool Level::use_charger(const ChargerType &type)
{
    _events.flush();

    switch (type) {
        case ChargerType::NORMAL:
            if (!move_player(_board->cursor()))
                return false;
            break;
        case ChargerType::RANDOM:
            move_player(_board->rand_coord(BoardSeekOption::ACCESSIBLE));
            break;
        case ChargerType::RANDOM_SAFE:
            move_player(
                _board->rand_coord(BoardSeekOption::ACCESSIBLE_NO_MONSTER));
            break;
    }

    resolve_events();
    return true;
}

const Links Level::get_links() const { return _links; }
