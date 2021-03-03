#include "AppGame.hpp"
#include "Controller/ControllerKeyboard.hpp"
#include "Model/Board/Board.hpp"
#include "Model/FileController/FileReader.hpp"
#include "Model/FileController/FileWriter.hpp"
#include "View/CLI/DisplayGameCLI.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

int main(int argc, char const *argv[])
{
    if (argc > 3)
        throw std::invalid_argument("Please launch with a game file");
    std::string loadFile(argv[1]);
    FileReader fr;
    Game *game = fr.readGame(loadFile);
    if (game == nullptr) {
        std::cout << "Could not read Game" << std::endl;
        return 1;
    }
    Display *display       = new DisplayGameCLI();
    Controller *controller;
    if(argc != 3)
      controller = new ControllerKeyboard<Layout_en_GB>();
    else {
      switch(str2int(argv[2])){
        case str2int("enGB") :
          controller = new ControllerKeyboard<Layout_en_GB>();
          break;
        case str2int("frFR") :
          controller = new ControllerKeyboard<Layout_fr_FR>();
          break;
        default :
          controller = new ControllerKeyboard<Layout_en_US>();
          break;

      }
    }
    AppGame *app           = new AppGame(controller, display);
    app->loop(game);
    return 0;
}
