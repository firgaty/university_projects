#ifndef INCLUDE_MODEL_CREATOR_OPTIONARGUMENTS_HPP_
#define INCLUDE_MODEL_CREATOR_OPTIONARGUMENTS_HPP_

enum MainArgumentsType { SQUARE, OBJECT };
enum ObjectArgumentsType { DIAMOND, CHARGER, PLAYER, MONSTER };
enum SquareArgumentsType { DOOR, WALL, NORMAL };


struct BaseSubOptionsArguments {
    
};

struct OptionsArguments {
    MainArgumentsType _type;
};

#endif // !INCLUDE_MODEL_CREATOR_OPTIONARGUMENTS_HPP_