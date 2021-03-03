#ifndef INCLUDE_CONTROLLER_INPUT_HPP_
#define INCLUDE_CONTROLLER_INPUT_HPP_

/**
 * @brief Input Flags
 *
 */
enum Input {
    LEFT       = (1 << 0),
    RIGHT      = (1 << 1),
    UP         = (1 << 2),
    DOWN       = (1 << 3),
    EXIT       = (1 << 4),
    ENTER      = (1 << 5),
    ERROR      = (1 << 6),
    BUT0       = (1 << 7),
    BUT1       = (1 << 8),
    BUT2       = (1 << 9),
    BUT3       = (1 << 10),
    BUT4       = (1 << 11),
    BUT5       = (1 << 12),
    BUT6       = (1 << 13),
    BUT7       = (1 << 14),
    BUT8       = (1 << 15),
    BUT9       = (1 << 16),
    UP_RIGHT   = UP | RIGHT,
    UP_LEFT    = UP | LEFT,
    DOWN_RIGHT = DOWN | RIGHT,
    DOWN_LEFT  = DOWN | LEFT
};

// Standard flag operator overloading
inline Input operator~(Input a) { return (Input) ~(int)a; }
inline Input operator|(Input a, Input b) { return (Input)((int)a | (int)b); }
inline Input operator&(Input a, Input b) { return (Input)((int)a & (int)b); }
inline Input operator^(Input a, Input b) { return (Input)((int)a ^ (int)b); }
inline Input &operator|=(Input &a, Input b)
{
    return (Input &)((int &)a |= (int)b);
}
inline Input &operator&=(Input &a, Input b)
{
    return (Input &)((int &)a &= (int)b);
}
inline Input &operator^=(Input &a, Input b)
{
    return (Input &)((int &)a ^= (int)b);
}

#endif //  INCLUDE_CONTROLLER_INPUT_HPP_
