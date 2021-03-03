#include "View/CLI/DisplayGameCLI.hpp"

DisplayGameCLI::DisplayGameCLI() : _main_view("Game Creator")
{
    _dimensions          = Dimensions(15, 100);
    VLayout *main_layout = new VLayout();
    HLayout *sec_layout  = new HLayout();

    // _layout.set_visible_separator(true);
    _level_display = new DisplayLevelCLI();
    _string_array.reserve(height());
    for (int i = 0; i < height(); i++)
        _string_array.push_back(std::u32string(width(), ' '));

    _level_group  = new GroupCLI("Board");
    _level_group ->set_element(_level_display);
    sec_layout->add_element(_level_group );

    _player_stats         = new DisplayPlayerStatsCLI();
    GroupCLI *stats_group = new GroupCLI("Stats");
    stats_group->set_element(_player_stats);

    sec_layout->add_element(stats_group);
    main_layout->set_gap(0);

    main_layout->add_element(sec_layout);

    _main_view.set_element(main_layout);

    _yes_no_group = new DisplayGroupCLI("Exit ?");
}
DisplayGameCLI::~DisplayGameCLI() {}

void DisplayGameCLI::set_game(Game *game)
{

    if (!(game) || game == _game)
        return;
    _game = game;
    set_state_fetched();

    _level_display->set_level(_game->get_current_level());
    _player_stats->set_stats(_game->get_player_stats());

    if ((_exit_yes_no_disp))
        delete _exit_yes_no_disp;
    _exit_yes_no_disp = new DisplayYesNoCLI(_game->get_exit_yes_no());
    _yes_no_group->set_element(_exit_yes_no_disp);

    gen_string_array();
    set_state_fetched();
}

void DisplayGameCLI::gen_string_array()
{
    if (_state == DisplayState::GENERATED)
        return;

    if (_game->get_ac_state() == ACState::EXIT_YES_NO) {

        _yes_no_group->gen_string_array();
        _string_array = _yes_no_group->get_string_array();
        dimensions(_yes_no_group->dimensions());

    } else {
        if((_game));{
            _level_display->set_level(_game->get_current_level());
            _level_group->set_element(_level_display);
        }

        _main_view.gen_string_array();
        _string_array = _main_view.get_string_array();
        dimensions(_main_view.dimensions());
    }

    set_state_generated();
}
