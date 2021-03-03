#ifndef INCLUDE_MODEL_STATISTICS_STATS_H_
#define INCLUDE_MODEL_STATISTICS_STATS_H_

using uint = unsigned int;

struct GameStats {
    GameStats()
        : _monster_killed(0), _distance_travelled(0), _diamonds_collected(0),
          _died(0), _changed_level(0), _charger_used_total(0),
          _charger_used_normal(0), _charger_used_random(0),
          _charger_used_safe_random(0)
    {
    }

    GameStats(uint mk,uint d, uint dt, uint dc, uint cl, uint ct, uint cn, uint cr, uint csr) :
    _monster_killed(mk),
    _died(d),
    _distance_travelled(dt),
    _diamonds_collected(dc),
    _changed_level(cl),
    _charger_used_total(ct),
    _charger_used_normal(cn),
    _charger_used_random(cr),
    _charger_used_safe_random(csr)
    {}

    uint _monster_killed;
    uint _died;

    uint _distance_travelled;
    uint _diamonds_collected;
    uint _changed_level;

    uint _charger_used_total;
    uint _charger_used_normal;
    uint _charger_used_random;
    uint _charger_used_safe_random;
};

#endif // ! INCLUDE_MODEL_STATISTICS_STATS_H_
