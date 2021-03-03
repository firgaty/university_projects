#ifndef INCLUDE_VIEW_CLI_DISPLAYGAMECLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYGAMECLI_HPP_

#include <vector>

#include "Model/Game.hpp"
#include "View/CLI/DisplayBlankCLI.hpp"
#include "View/CLI/DisplayBoxCLI.hpp"
#include "View/CLI/DisplayCLI.hpp"
#include "View/CLI/DisplayChoiceSelectCLI.hpp"
#include "View/CLI/DisplayGroupCLI.hpp"
#include "View/CLI/DisplayLabelCLI.hpp"
#include "View/CLI/DisplayLevelCLI.hpp"
#include "View/CLI/DisplayNumerBoxCLI.hpp"
#include "View/CLI/DisplayPlayerStatsCLI.hpp"
#include "View/CLI/DisplaySeperatorCLI.hpp"
#include "View/CLI/Layout/HLayout.hpp"
#include "View/CLI/Layout/VLayout.hpp"

class DisplayGameCLI : public virtual DisplayCLI
{
private:
    Game *_game = nullptr;
    StringArray _base;
    GroupCLI _main_view;
    DisplayLevelCLI *_level_display      = nullptr;
    DisplayPlayerStatsCLI *_player_stats = nullptr;
    DisplayYesNoCLI *_exit_yes_no_disp   = nullptr;
    DisplayGroupCLI *_yes_no_group       = nullptr;
    GroupCLI *_level_group               = nullptr;

public:
    DisplayGameCLI();
    ~DisplayGameCLI();

    // void display() const;
    void gen_string_array();

    void set_game(Game *game);
};

#endif // !INCLUDE_VIEW_CLI_DISPLAYGAMECLI_HPP_