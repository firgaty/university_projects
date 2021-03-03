#ifndef INCLUDE_VIEW_CLI_DISPLAYLEVELCLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYLEVELCLI_HPP_

#include "DisplayBoardCLI.hpp"
#include "DisplayCLI.hpp"
#include "Model/Level.hpp"

class DisplayLevelCLI : public virtual DisplayCLI
{
private:
    Level *_level           = nullptr;
    DisplayBoardCLI *_board = nullptr;

public:
    DisplayLevelCLI();
    DisplayLevelCLI(Level *level);
    ~DisplayLevelCLI();

    // void display() const;
    void gen_string_array();

    void set_level(Level *level);
};

#endif // !INCLUDE_VIEW_CLI_DISPLAYLEVELCLI_HPP_