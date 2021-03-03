#ifndef INCLUDE_VIEW_CLI_DISPLAYPLAYERSTATSLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYPLAYERSTATSLI_HPP_

#include "Model/Statistics/PlayerStats.hpp"
#include "View/CLI/DisplayCLI.hpp"
#include "View/CLI/DisplayContainerCLI.hpp"
#include "View/CLI/DisplayLabelCLI.hpp"
#include "View/CLI/DisplayNumerBoxCLI.hpp"
#include "View/CLI/Layout/HLayout.hpp"
#include "View/CLI/Layout/VLayout.hpp"

class DisplayPlayerStatsCLI : public virtual DisplayContainerCLI
{
private:
    const PlayerStats *_stats;

    NumberBoxCLI *_box_chr, *_box_chr_rand, *_box_chr_safe, *_box_diamonds;

public:
    DisplayPlayerStatsCLI();
    DisplayPlayerStatsCLI(const PlayerStats *stats);
    ~DisplayPlayerStatsCLI();
    void gen_string_array();
    void set_stats(const PlayerStats *stats);
};

using PlayerStatsCLI = DisplayPlayerStatsCLI;

#endif // ! INCLUDE_VIEW_CLI_DISPLAYPLAYERSTATSLI_HPP_