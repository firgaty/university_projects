#include <cstdlib>
#include <iostream>

#include "AppCreator.hpp"
#include "Model/Board/Door.hpp"
#include "Model/ChoiceSelect.hpp"
#include "Model/GameObject/Monster/MonsterTypes.hpp"
#include "Model/MoveSet/SquareMoveSet.hpp"
#include "View/CLI/DisplayBoardCLI.hpp"
#include "View/CLI/DisplayBoardCreatorCLI.hpp"
#include "View/CLI/DisplayChoiceSelectCLI.hpp"
#include "View/CLI/DisplayGameCLI.hpp"
#include "View/CLI/DisplayGameCreator.hpp"
#include "View/CLI/DisplayLevelCLI.hpp"

AppCreator::AppCreator(ControllerBase *controller, Display *view)
    : AppBase(controller, view)
{
}
AppCreator::~AppCreator() {}

int AppCreator::loop()
{
    Input in;
    GameCreator creator;
    DisplayGameCreatorCLI disp(&creator);

    while (1) {
        std::system("clear");
        disp.gen_string_array();
        disp.display();
        in = _controller->input();

        if (creator.act_on_input(in) == ACTION_EXIT) {
            exit(0);
        }
    }
    return 0;
}
