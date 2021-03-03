#ifndef INCLUDE_VIEW_CLI_DISPLAYBOARDCREATOR_HPP_
#define INCLUDE_VIEW_CLI_DISPLAYBOARDCREATOR_HPP_

#include "Model/Creator/BoardCreator.hpp"
#include "View/CLI/DisplayBoardCLI.hpp"
#include "View/CLI/DisplayChoiceSelectCLI.hpp"
#include "View/CLI/DisplayGroupCLI.hpp"
#include "View/CLI/DisplayNumberSelectorCLI.hpp"
#include "View/CLI/Layout/HLayout.hpp"
#include "View/CLI/Layout/VLayout.hpp"

class DisplayBoardCreatorCLI : public DisplayContainerCLI
{
private:
    BoardCreator *_creator;
    DisplayNumberSelectorCLI *_n_selector;
    DisplayChoiceSelectCLI *_menu;
    DisplayBoardCLI *_board;
    YesNoCLI *_yes_no;
    GroupCLI *_group;
    Layout *_layout;

    void cleanup()
    {
        if ((_n_selector))
            delete _n_selector;
        if ((_menu))
            delete _menu;
        if ((_board))
            delete _board;
        if ((_yes_no))
            delete _yes_no;
        if ((_group)) {
            _group->unset_element();
            delete _group;
        }
        if ((_layout))
            delete _layout;
        _creator    = nullptr;
        _n_selector = nullptr;
        _menu       = nullptr;
        _board      = nullptr;
        _yes_no     = nullptr;
        _group      = nullptr;
        _layout     = nullptr;
    }

public:
    DisplayBoardCreatorCLI()
    {
        _creator    = nullptr;
        _n_selector = nullptr;
        _menu       = nullptr;
        _board      = nullptr;
        _yes_no     = nullptr;
        _group      = nullptr;
        _layout     = nullptr;
    }
    DisplayBoardCreatorCLI(BoardCreator *creator) : DisplayBoardCreatorCLI()
    {

        set_board_creator(creator);
    }
    ~DisplayBoardCreatorCLI()
    {
        switch (_creator->get_ac_state()) {
            case ACState::MENU0:
                delete _yes_no;
                delete _layout;
                break;
            case ACState::EXIT_YES_NO:
                delete _layout;
                delete _n_selector;
                break;
            case ACState::CATCH:
                delete _n_selector;
                delete _yes_no;
                break;
        }
    }

    void set_board_creator(BoardCreator *creator)
    {
        cleanup();
        _creator    = creator;
        _n_selector = new DisplayNumberSelectorCLI(creator->number_selector());
        _menu       = new DisplayChoiceSelectCLI(creator->board_options());
        _yes_no     = new YesNoCLI(creator->get_exit_yes_no());
        _board      = new DisplayBoardCLI();
        _group      = new GroupCLI("Dimensions", _n_selector);
        set_element(_group);
        _layout = new HLayout();
        _layout->add_element(new GroupCLI("Board", _board));
        _layout->add_element(new GroupCLI("Squares", _menu));
        _menu->set_labels({"1: Empty",
                           "2: Wall",
                           "3: Door (Closed)",
                           "4: Door (Open)",
                           "5: Goal (Closed)",
                           "6: Goal (Open)"});
    }

    void gen_string_array()
    {
        switch (_creator->get_ac_state()) {
            case ACState::MENU0:
                _group->set_title("Dimensions");
                _group->set_element(_n_selector);
                break;
            case ACState::EXIT_YES_NO:
                _group->set_title("Continue ?");
                _group->set_element(_yes_no);
                break;
            case ACState::CATCH:
                _board->set_board(_creator->board());
                _group->set_title("Board Creator");
                _group->set_element(_layout);
                break;
        }
        _element->gen_string_array();
        _string_array = _element->get_string_array();
    }
};

#endif // !INCLUDE_VIEW_CLI_DISPLAYBOARDCREATOR_HPP_