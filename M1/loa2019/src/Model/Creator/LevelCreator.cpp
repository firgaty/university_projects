#include "Model/Creator/LevelCreator.hpp"
#include "Model/GameObject/GameObjectState.hpp"

// LevelCreator::LevelCreator() { std::cout << "\n"; }

void LevelCreator::remove_monster(const Point2D_u &coord)
{
    _monster_states.remove(coord);
}
void LevelCreator::remove_diamond(const Point2D_u &coord)
{
    _diamond_states.remove(coord);
}
void LevelCreator::remove_charger(const Point2D_u &coord)
{
    _charger_states.remove(coord);
}
void LevelCreator::remove_game_objects(const Point2D_u &coord)
{
    if (!_board->is_in_grid(coord))
        return;
    Square *s           = _board->get_square(coord);
    const GameObject *o = nullptr;
    while (!s->is_empty()) {
        o = s->remove_last();
        if (Player::is_this_type(o)) {
            remove_player();
        } else if (Diamond::is_this_type(o)) {
            remove_diamond(o);
        } else if (Charger::is_this_type(o)) {
            remove_charger(o);
        } else if (Monster::is_this_type(o)) {
            remove_monster(o);
        } else {
            // TODO: send error event
        }
    }
}
void LevelCreator::remove_player()
{
    _board->remove_object(_player_state._object, _player_state._coord);
    _player_state._coord = Point2D_u(-1, -1); // out of board
    delete (_player_state._object);
}

void LevelCreator::remove_monster(const GameObject *m)
{
    _monster_states.remove(m);
}
void LevelCreator::remove_diamond(const GameObject *d)
{
    _diamond_states.remove(d);
}
void LevelCreator::remove_charger(const GameObject *c)
{
    _charger_states.remove(c);
}

void LevelCreator::remove_monster() { remove_monster(_board->cursor()); }
void LevelCreator::remove_diamond() { remove_diamond(_board->cursor()); }
void LevelCreator::remove_charger() { remove_charger(_board->cursor()); }
void LevelCreator::remove_game_objects()
{
    remove_game_objects(_board->cursor());
}

void LevelCreator::remove_link(const Point2D_u &diamond, const Point2D_u door)
{
    _links.remove(diamond, door);
}

void LevelCreator::remove_link(const Point2D_u &coord) { _links.remove(coord); }