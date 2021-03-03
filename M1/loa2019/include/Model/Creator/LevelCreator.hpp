#ifndef INCLUDE_MODEL_CREATOR_LEVELCREATOR_HPP_
#define INCLUDE_MODEL_CREATOR_LEVELCREATOR_HPP_

#include "Model/Level.hpp"
#include "Model/NumberSelector.hpp"

using EditorOptions = ActionableChoiceSelect<CSButAction<true>>;

class LevelCreator : public Level
{
private:
    void remove_monster(const GameObject *m);
    void remove_diamond(const GameObject *d);
    void remove_charger(const GameObject *c);

public:
    LevelCreator() : Level() {}
    // LevelCreator(Level level);
    ~LevelCreator() {}

    // remove methods for GameCreator mode.
    void remove_monster(const Point2D_u &coord);
    void remove_monster();
    void remove_diamond(const Point2D_u &coord);
    void remove_diamond();
    void remove_charger(const Point2D_u &coord);
    void remove_charger();
    void remove_game_objects(const Point2D_u &coord);
    void remove_game_objects();
    void remove_player();

    void remove_link(const Point2D_u& diamond, const Point2D_u door);
    void remove_link(const Point2D_u& coord);
};

#endif // !INCLUDE_MODEL_CREATOR_LEVELCREATOR_HPP_