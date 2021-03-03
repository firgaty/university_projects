#include "AppCreator.hpp"
#include "Controller/ControllerKeyboard.hpp"
#include <fstream>
#include <iostream>
#include <locale>

bool check_if_file_exists(std::string const &path)
{
    std::ifstream test(path);
    if (!test) {
        std::cout << "Le fichier n'existe pas" << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "");
    std::cout << "Creator !" << std::endl;
    AppCreator app(new ControllerKeyboard<Layout_en_GB>(), nullptr);
    app.loop();
    return 0;
}
