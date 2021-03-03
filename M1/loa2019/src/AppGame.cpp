#include <cstdlib>
#include <iostream>

#include "AppGame.hpp"
#include "Model/Board/Door.hpp"
#include "Model/ChoiceSelect.hpp"
#include "Model/GameObject/Monster/MonsterTypes.hpp"
#include "Model/MoveSet/SquareMoveSet.hpp"
#include "View/CLI/DisplayBoardCLI.hpp"
#include "View/CLI/DisplayChoiceSelectCLI.hpp"
#include "View/CLI/DisplayGameCLI.hpp"
#include "View/CLI/DisplayLevelCLI.hpp"

AppGame::AppGame(ControllerBase *controller, Display *view)
    : AppBase(controller, view)
{
}
AppGame::~AppGame() {}

int AppGame::loop(Game *&game)
{
    int i = 0;
    Input in;
    DisplayGameCLI disp;
    disp.set_game(game);
    while (1) {
        std::system("clear");
        disp.gen_string_array();
        disp.display();
        in = _controller->input();

        i++;

        if (game->act_on_input(in) == ACTION_EXIT)
            exit(0);
    }
    return 0;
}

int AppGame::loop() { return 0; }
