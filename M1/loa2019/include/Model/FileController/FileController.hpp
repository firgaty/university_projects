#ifndef INCLUDE_MODEL_FILECONTROLLER_FILECONTROLLER_HPP_
#define INCLUDE_MODEL_FILECONTROLLER_FILECONTROLLER_HPP_

#define SQUARE_WALL 'O'
#define SQUARE_EMPTY ' '
#define SQUARE_DOOR_OPEN '-'
#define SQUARE_DOOR_CLOSED '+'
#define SQUARE_DOOR_GOAL_OPEN 'x'
#define SQUARE_DOOR_GOAL_CLOSED 'X'
#define F_MONSTER 'm'
#define F_PLAYER 'p'
#define F_DIAMOND 'd'
#define F_COMMENT ';'
#define F_NB_OBJ 'o'
#define F_BOARD_SIZE '#'
#define F_CHARGER 'c'
#define F_DOOR_LINK 'l'
#define F_LEVEL_LINK 'L'
#define F_CURRENT_LEVEL 'C'
#define F_PLAYER_STATS 's'
#define F_GAME_STATS 'S'

#include <fstream>
#include <iostream>
#include "Model/Game.hpp"



class FileController{

};

#endif // INCLUDE_MODEL_FILECONTROLLER_FILECONTROLLER_HPP_
