#include "View/CLI/DisplayPlayerStatsCLI.hpp"

DisplayPlayerStatsCLI::DisplayPlayerStatsCLI()
{
    _stats        = nullptr;
    _string_array = StringArray();

    HLayout *main_layout = new HLayout();

    _box_chr      = new NumberBoxCLI(0, 4);
    _box_chr_rand = new NumberBoxCLI(0, 4);
    _box_chr_safe = new NumberBoxCLI(0, 4);
    _box_diamonds = new NumberBoxCLI(0, 4);

    VLayout *left  = new VLayout();
    VLayout *right = new VLayout();
    left->set_gap(0);
    right->set_gap(0);

    left->add_element(new LabelCLI("Chr norm:"));
    right->add_element(_box_chr);
    left->add_element(new LabelCLI("Chr rand:"));
    right->add_element(_box_chr_rand);
    left->add_element(new LabelCLI("Chr safe:"));
    right->add_element(_box_chr_safe);
    left->add_element(new LabelCLI("Diamonds:"));
    right->add_element(_box_diamonds);

    main_layout->add_element(left);
    main_layout->add_element(right);
    main_layout->set_gap(0);

    _element = main_layout;
    _element->gen_string_array();
    _dimensions = _element->dimensions();
}
DisplayPlayerStatsCLI::DisplayPlayerStatsCLI(const PlayerStats *stats)
    : DisplayPlayerStatsCLI()
{
    set_stats(stats);
}

DisplayPlayerStatsCLI::~DisplayPlayerStatsCLI() {}
void DisplayPlayerStatsCLI::gen_string_array()
{
    if (_state == DisplayState::GENERATED)
        return;
    _string_array.clear();
    if ((_stats)) {
        _box_chr->set_value(_stats->_charger);
        _box_chr_rand->set_value(_stats->_charger_random);
        _box_chr_safe->set_value(_stats->_charger_safe_random);
        _box_diamonds->set_value(_stats->_diamonds);
    }
    _element->gen_string_array();
    _dimensions   = _element->dimensions();
    _string_array = _element->get_string_array();
    _state        = DisplayState::GENERATED;
}
void DisplayPlayerStatsCLI::set_stats(const PlayerStats *stats)
{
    set_state_fetched();
    _stats = stats;
}