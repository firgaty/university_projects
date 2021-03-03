#ifndef INCLUDE_APPGAME_HPP_
#define INCLUDE_APPGAME_HPP_

#include "AppBase.hpp"
#include "Model/Game.hpp"


class AppGame : public virtual AppBase
{
public:
    AppGame(ControllerBase * controller, Display * view);
    ~AppGame();
    int loop(Game * &game) ;
    int loop();
};

#endif // INCLUDE_APPGAME_HPP_
