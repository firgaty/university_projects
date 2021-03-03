#ifndef INCLUDE_MODEL_GAME_H_
#define INCLUDE_MODEL_GAME_H_

#include <vector>

#include "Model/Actionable.hpp"
#include "Model/ChoiceSelect.hpp"
#include "Model/Event/Event.hpp"
#include "Model/Level.hpp"
#include "Model/LevelLinks.hpp"
#include "Model/Statistics/GameStats.hpp"
#include "Model/Statistics/PlayerStats.hpp"

#define WINNER_LEVEL 1337


using Levels = std::vector<Level *>;

enum class GameState { NORMAL, CHARGER };

class Game : public virtual ExitYesNoContainer
{
protected:
    Levels *_levels;
    Level *_current_level = nullptr;
    size_t _level_index;
    LevelLinks _links; // If a level is erased, all links must be moved/updated
    GameStats *_game_stats        = nullptr;
    PlayerStats *_player_stats    = nullptr;
    LevelEventQueue *_event_queue = nullptr;
    GameState _state              = GameState::NORMAL;

    void resolve_events();
    void resolve_door_event(const LevelEvent &e);
    void resolve_lose_event(const LevelEvent &e);
    void resolve_no_charger_event(const LevelEvent &e);
    void resolve_no_diamonds_event(const LevelEvent &e);
    void resolve_no_monster_event(const LevelEvent &e);

    virtual ActionOutput on_actionable_element_exit();

public:
    Game();
    ~Game();

    bool add_level(Level *l);
    bool add_link(const size_t from,
                  const Point2D_u from_coord,
                  const size_t to,
                  const Point2D_u to_coord,
                  const bool bothways = true);

    bool set_current_level(const size_t &index);
    bool set_current_level(const size_t &index, const Point2D_u pos);
    void set_game_stats(GameStats *s);
    void set_player_stats(PlayerStats *s);

    // Getters
    const LevelLinks  get_level_links() const;
    const GameStats *get_game_stats() const;
    const PlayerStats *get_player_stats() const;
    Level *get_current_level();
    Levels *get_levels();
    size_t &get_level_index();

    void reset();

    virtual ActionOutput internal_act_on_input(const Input &input);
};

#endif // !INCLUDE_MODEL_GAME_H_
