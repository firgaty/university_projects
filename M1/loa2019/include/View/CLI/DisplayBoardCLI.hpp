#ifndef INCLUDE_VIEW_CLI_DISPLAYBOARDCLI_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYBOARDCLI_HPP_

#include "DisplayCLI.hpp"
#include "Model/Board/Board.hpp"
#include "Model/Color.hpp"
#include "View/CLI/DisplayBlankCLI.hpp"

class DisplayBoardCLI : virtual public DisplayCLI
{
private:
    const Board *_board = nullptr;

public:
    DisplayBoardCLI();
    ~DisplayBoardCLI() {}
    DisplayBoardCLI(const Board *board);
    DisplayBoardCLI(const DisplayBoardCLI &) = delete;
    void operator=(const DisplayBoardCLI &) = delete;

    void gen_string_array();

    void set_board(const Board *);

    void x(unsigned int x) = delete;
    void y(unsigned int y) = delete;
};

#endif //  INCLUDE_VIEW_CLI_DISPLAYBOARDCLI_HPP_
