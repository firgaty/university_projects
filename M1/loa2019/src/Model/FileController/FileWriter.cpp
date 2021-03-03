#include "Model/FileController/FileWriter.hpp"

FileWriter::FileWriter() {}

FileWriter::~FileWriter() {}

void writeGrid(Board const *board, std::ofstream *boardFile);
void writeObjects(Level const *level, std::ofstream *boardFile);
void writePlayer(Level const *level, std::ofstream *boardFile);
void writeLinks(Level const *level, std::ofstream *boardFile);
void writeLevelLinks(Game *&game, std::ofstream *boardFile);
void writeCurrentLevel(Game *&game, std::ofstream *boardFile);
void writeStats(Game *&game, std::ofstream *boardFile);

bool FileWriter::writeBoardFile(Game *game, std::string const path)
{
    std::ofstream boardFile(path.c_str(), std::ios::out);
    for (Level *level : *(game->get_levels())) {
        boardFile << "#" << level->board()->x() << " " << level->board()->y()
                  << std::endl;
        writeGrid(level->board(), &boardFile);
        writePlayer(level, &boardFile);
        writeObjects(level, &boardFile);
        writeLinks(level, &boardFile);
    }
    writeLevelLinks(game, &boardFile);
    writeCurrentLevel(game, &boardFile);
    writeStats(game, &boardFile);
    boardFile.close();
    return true;
}

void writeGrid(Board const *board, std::ofstream *boardFile)
{
    for (int i = 0; i < board->x(); i++) {
        for (int j = 0; j < board->y(); j++) {
            char charToWrite;
            switch (board->get_square(i, j)->color()) {
                case Color::WALL1: charToWrite = SQUARE_WALL; break;
                case Color::EMPTY: charToWrite = SQUARE_EMPTY; break;
                case Color::DOOR_OPEN: charToWrite = SQUARE_DOOR_OPEN; break;
                case Color::DOOR_CLOSE: charToWrite = SQUARE_DOOR_CLOSED; break;
                case Color::DOOR_GOAL_OPEN:
                    charToWrite = SQUARE_DOOR_GOAL_OPEN;
                    break;
                case Color::DOOR_GOAL_CLOSE:
                    charToWrite = SQUARE_DOOR_GOAL_CLOSED;
                    break;
                default: charToWrite = 'E'; break;
            }
            *boardFile << charToWrite;
        }
        *boardFile << std::endl;
    }
}

void writePlayer(Level const *level, std::ofstream *boardFile)
{
    *boardFile << F_PLAYER << " " << level->player_state()._coord.x() << " "
               << level->player_state()._coord.y() << std::endl;
}

void writeObjects(Level const *level, std::ofstream *boardFile)
{
    for (DiamondObjectState state : level->diamond_states()) {
        *boardFile << F_DIAMOND << " " << state._coord.x() << " "
                   << state._coord.y() << std::endl;
    }

    for (MonsterObjectState state : level->monster_states()) {
        int ms;
        switch (state._object->get_move_set()->getmsID()) {
            case MoveSetIDs::CROSS_MOVE: ms = 0; break;
            case MoveSetIDs::DIAGONAL_CROSS_MOVE: ms = 1; break;
            case MoveSetIDs::SQUARE: ms = 2; break;
            default: ms = 9; break;
        }
        int monCol = state._object->color();
        *boardFile << F_MONSTER << " " << state._coord.x() << " "
                   << state._coord.y() << " MON" << monCol << " " << ms << " "
                   << 0 << std::endl;
    }

    for (ChargerObjectState state : level->charger_states()) {
        int type;
        switch (state._object->get_type()) {
            case ChargerType::RANDOM: type = 0; break;
            case ChargerType::RANDOM_SAFE: type = 1; break;
            default: type = 9; break;
        }
        *boardFile << F_CHARGER << " " << state._coord.x() << " "
                   << state._coord.y() << " " << type << std::endl;
    }
}

void writeLinks(Level const *level, std::ofstream *boardFile)
{
    for (Link l : level->get_links().get_links()) {
        *boardFile << F_DOOR_LINK << " " << l._diamond_coord.x() << " "
                   << l._diamond_coord.y() << " " << l._door_coord.x() << " "
                   << l._door_coord.y() << std::endl;
    }
}

void writeLevelLinks(Game *&game, std::ofstream *boardFile)
{
    for (LevelLink l : game->get_level_links().get_links()) {
        *boardFile << F_LEVEL_LINK << " " << l._from._id << " "
                   << l._from._coord.x() << " " << l._from._coord.y() << " "
                   << l._to._id << " " << l._to._coord.x() << " "
                   << l._to._coord.y() << std::endl;
    }
}

void writeCurrentLevel(Game *&game, std::ofstream *boardFile)
{
    std::size_t cur_level = game->get_level_index();
    Point2D coord         = game->get_current_level()->player_state()._coord;
    *boardFile << F_CURRENT_LEVEL << " " << cur_level << " " << coord.x() << " "
               << coord.y() << std::endl;
}

void writeStats(Game *&game, std::ofstream *boardFile)
{
    const PlayerStats *ps = game->get_player_stats();
    const GameStats *gs   = game->get_game_stats();
    *boardFile << F_PLAYER_STATS << " " << ps->_charger << " "
               << ps->_charger_random << " " << ps->_charger_safe_random << " "
               << ps->_diamonds << std::endl;
    *boardFile << F_GAME_STATS << " " << gs->_monster_killed << " " << gs->_died
               << " " << gs->_distance_travelled << " "
               << gs->_diamonds_collected << " " << gs->_changed_level << " "
               << gs->_charger_used_total << " " << gs->_charger_used_normal
               << " " << gs->_charger_used_random << " "
               << gs->_charger_used_safe_random << std::endl;
}
