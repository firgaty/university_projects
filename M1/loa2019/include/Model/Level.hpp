#ifndef INCLUDE_LEVEL_HPP_
#define INCLUDE_LEVEL_HPP_

#include <vector>

#include "Event/Event.hpp"
#include "GameObject/Charger.hpp"
#include "GameObject/Diamond.hpp"
#include "GameObject/GameObjectState.hpp"
#include "GameObject/Monster/Monster.hpp"
#include "GameObject/Player.hpp"
#include "Model/Actionable.hpp"
#include "Model/Board/Board.hpp"
#include "Model/Links.hpp"

#define STATE_VECTOR_INIT_SIZE 32

using MoveableObjectState = GameObjectState<Moveable *>;
using PlayerObjectState   = GameObjectState<Player *>;
using MonsterObjectState  = GameObjectState<Monster *>;
using ChargeObjectState   = GameObjectState<Charger *>;
using DiamondObjectState  = GameObjectState<Diamond *>;

enum class LevelState { PLAY, SELECT };

class Level : public virtual ActionableContainer
{
protected:
    Board *_board;
    MonsterObjectStateVector _monster_states;
    DiamondObjectStateVector _diamond_states;
    ChargerObjectStateVector _charger_states;
    PlayerObjectState _player_state;
    LevelState _state;
    Links _links; // Diamond to door links
    BoardEventQueue _events;
    LevelEventQueue *_level_events = nullptr;

    bool play_turn(const Input &input);
    void resolve_events();
    void resolve_object_event(const BoardEvent &e);
    void resolve_door_event(const BoardEvent &e);
    void resolve_door_link(const Diamond *d);
    void remove_from_board(const GameObject *o);
    void add_level_event(const LevelEvent e);

    virtual ActionOutput on_actionable_element_exit();

public:
    Level();
    virtual ~Level();

    // setters
    void set_board(Board *board);
    bool set_monster(Monster *monster,
                     Point2D_u coord,
                     Point2D_u coord_init,
                     bool on_board = true);
    bool set_monster(Monster *monster, Point2D_u coord, bool on_board = true);
    bool set_monster(Monster *monster);
    bool set_diamond(Diamond *diamond,
                     Point2D_u coord,
                     Point2D_u coord_init,
                     bool on_board = true);
    bool set_diamond(Diamond *diamond, Point2D_u coord, bool on_board = true);
    bool set_diamond(Diamond *diamond);
    bool set_charger(Charger *charger,
                     Point2D_u coord,
                     Point2D_u coord_init,
                     bool on_board = true);
    bool set_charger(Charger *charger, Point2D_u coord, bool on_board = true);
    bool set_charger(Charger *charger);
    bool set_player(Point2D_u coord);
    bool set_player();

    bool set_link(Point2D_u diamond_coor, Point2D_u door_coord);
    bool set_level_event_queue(LevelEventQueue *queue);

    void set_state_select();
    void set_state_play();
    void set_level_num(int num);

    // getters
    const LevelState &state() const;
    const Board *board() const;
    const PlayerObjectState &player_state() const;
    const std::vector<MonsterObjectState> &monster_states() const;
    const std::vector<DiamondObjectState> &diamond_states() const;
    const std::vector<ChargerObjectState> &charger_states() const;
    const int &level_num() const;
    const Links  get_links() const ;

    // move methods
    Point2D_u pos_from_input(const Input &input,
                             Point2D_u pos = Point2D_u()) const;
    bool move_player(const Input &input);
    bool move_player(const Point2D_u &coord);
    bool move_cursor(const Input &input,
                     const BoardSeekOption &seek = BoardSeekOption::ALL);
    bool move_cursor(const Point2D_u &coord);
    bool move_monsters();
    bool move_monster(MonsterObjectState &state, const Point2D_u &to);
    bool move_moveable(const Moveable *m,
                       const Point2D_u &from,
                       const Point2D_u &to);

    virtual ActionOutput internal_act_on_input(const Input &input);

    bool use_charger(const ChargerType &type);
};

#endif // INCLUDE_LEVEL_HPP_
