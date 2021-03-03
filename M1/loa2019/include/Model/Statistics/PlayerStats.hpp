#ifndef INCLUDE_MODEL_STATISTICS_PLAYERSTATS_H_
#define INCLUDE_MODEL_STATISTICS_PLAYERSTATS_H_

using uint = unsigned int;

struct PlayerStats {
    uint _charger;
    uint _charger_random;
    uint _charger_safe_random;
    uint _diamonds;

    PlayerStats() : _charger(0), _charger_random(0), _charger_safe_random(0), _diamonds(0) {}
    PlayerStats(uint c, uint cr, uint csr, uint d) : _charger(c), _charger_random(cr), _charger_safe_random(csr), _diamonds(d) {}
};

#endif // !INCLUDE_MODEL_STATISTICS_PLAYERSTATS_H_
