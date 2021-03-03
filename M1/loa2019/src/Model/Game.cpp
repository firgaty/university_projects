#include "Model/Game.hpp"

#include <iostream>

Game::Game() : _state(GameState::NORMAL)
{
    _level_index = 0;
    _levels      = new Levels();
    _levels->reserve(16);

    _links = LevelLinks();

    _game_stats   = new GameStats();
    _player_stats = new PlayerStats();

    _event_queue = new LevelEventQueue();
}
Game::~Game()
{
    // delete all level, _current_level included
    for (auto e : *_levels)
        delete e;
    _levels->clear();

    // delete stats
    delete _game_stats;
    delete _player_stats;
    delete _event_queue;
}

bool Game::add_level(Level *l)
{
    // TODO: Check if level exists
    _levels->push_back(l);
    return true;
}

bool Game::add_link(const size_t from,
                    const Point2D_u from_coord,
                    const size_t to,
                    const Point2D_u to_coord,
                    const bool bothways)
{
    _links.set(from, from_coord, to, to_coord, bothways);
    return true;
}

bool Game::set_current_level(const size_t &index)
{
    if (index < _levels->size()) {
        _current_level = _levels->at(index);
        _level_index   = index;
        _current_level->set_level_event_queue(_event_queue);
        return true;
    }
    return false;
}

void Game::set_game_stats(GameStats *s)
{
    if (!(s))
        return;
    delete _game_stats;
    _game_stats = s;
}
void Game::set_player_stats(PlayerStats *s)
{
    if (!(s))
        return;
    delete _player_stats;
    _player_stats = s;
}

const GameStats *Game::get_game_stats() const { return _game_stats; }
const PlayerStats *Game::get_player_stats() const { return _player_stats; }
Level *Game::get_current_level() { return _current_level; }
Levels *Game::get_levels() { return _levels; }
size_t &Game::get_level_index() { return _level_index; }

ActionOutput Game::internal_act_on_input(const Input &input)
{
    // catch all relevant input
    ActionOutput out = ExitYesNoContainer::internal_act_on_input(input);

    if (out != ACTION_FAILED)
        return out;

    switch (input) {
        case ENTER:
            switch (_state) {
                case GameState::NORMAL: break;
                case GameState::CHARGER:
                    if (_current_level->use_charger(ChargerType::NORMAL)) {
                        _player_stats->_charger--;
                        _current_level->set_state_play();
                        _state = GameState::NORMAL;
                    }
                    goto post_switch;
            }
        case BUT1:
            if (_state == GameState::CHARGER) {
                _current_level->set_state_play();
                _state = GameState::NORMAL;
            } else if (_player_stats->_charger > 0)
                if (_current_level->state() == LevelState::PLAY) {
                    _current_level->set_state_select();
                    _state = GameState::CHARGER;
                }
            return ACTION_FAILED;
        case BUT2:
            if (_player_stats->_charger_random > 0) {
                _current_level->use_charger(ChargerType::RANDOM);
                _player_stats->_charger_random--;
            } else
                return ACTION_FAILED;
            break;
        case BUT3:
            if (_player_stats->_charger_safe_random > 0) {
                _current_level->use_charger(ChargerType::RANDOM_SAFE);
                _player_stats->_charger_safe_random--;
            } else
                return ACTION_FAILED;
            break;

        default: out = _current_level->act_on_input(input); break;
    }
post_switch:
    resolve_events();

    return out;
}

ActionOutput Game::on_actionable_element_exit()
{
    ActionOutput out = ExitYesNoContainer::on_actionable_element_exit();

    // if (out != ACTION_FAILED)
    //     return out;
    // switch (_actionable_type) {
    // }

    return out;
}

void Game::resolve_events()
{
    while (!_event_queue->empty()) {
        LevelEvent e = _event_queue->pop_front();
        switch (e._type) {
            case LevelEventType::DOOR: resolve_door_event(e); break;
            case LevelEventType::LOSE: resolve_lose_event(e); break;
            case LevelEventType::NO_CHARGER: resolve_no_charger_event(e); break;
            case LevelEventType::NO_DIAMONDS:
                resolve_no_diamonds_event(e);
                break;
            case LevelEventType::NO_MONSTER: resolve_no_monster_event(e); break;
            case LevelEventType::DIAMOND: _player_stats->_diamonds++; break;
            case LevelEventType::CHARGER:
                switch (e._body._charger_type) {
                    case ChargerType::NORMAL: _player_stats->_charger++; break;
                    case ChargerType::RANDOM:
                        _player_stats->_charger_random++;
                        break;
                    case ChargerType::RANDOM_SAFE:
                        _player_stats->_charger_safe_random++;
                        break;
                }
                break;
        }
    }
}

void Game::resolve_door_event(const LevelEvent &e)
{
    Square *s = _levels->at(_level_index)->board()->get_square(e._body._coord);
    if (Door::is_this_type(s) && dynamic_cast<const Door *>(s)->is_goal()) {
        const char *winner_msg
            = "_____________________________  \n"
              "< FELICITATIONS! TU AS GAGNE! >\n"
              " ----------------------------- \n"
              "        \\   ^__^               \n"
              "         \\  (oo)\\_______       \n"
              "            (__)\\       )\\/\\   \n"
              "                ||----w |      \n"
              "                ||     ||      \n"
              "_______________________________\n";
        std::cout << winner_msg << std::endl;
        exit(0);
    }
    if (!_links.has(_level_index, e._body._coord))
        return;
    SquareID id = _links.get(_level_index, e._body._coord);
    if (set_current_level(id._id))
        _current_level->set_player(id._coord);
}

const LevelLinks Game::get_level_links() const { return _links; }

// TODO
void Game::resolve_lose_event(const LevelEvent &e) {}
// TODO
void Game::resolve_no_charger_event(const LevelEvent &e) {}
// TODO
void Game::resolve_no_diamonds_event(const LevelEvent &e) {}
// TODO
void Game::resolve_no_monster_event(const LevelEvent &e) {}
