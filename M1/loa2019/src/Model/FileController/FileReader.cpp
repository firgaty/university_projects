#include "Model/FileController/FileReader.hpp"

FileReader::FileReader() {}

FileReader::~FileReader() {}

Level *parseLevel(std::string const &line, std::ifstream *boardFile);
int getNbObj(std::string const &line);
void addDiamond(Level *&level, std::string const &line);
void addPlayer(Level *&level, std::string const &line);
void addMonster(Level *&level, std::string const &line);
void addCharger(Level *&level, std::string const &line);
void addDoorLink(Level *&level, std::string const &line);
Color getMonsterColor(std::string s);
void buildBoard(Board *&board, std::ifstream *boardFile);
void addLevelLink(Game *&game, std::string const &line);
void addCurrentLevel(Game *&game, std::string const &line);
void addPlayerStats(Game *&game, std::string const &line);
void addGameStats(Game *&game, std::string const &line);

Game *FileReader::readGame(std::string const &path)
{
    std::ifstream boardFile(path);
    Game *game = new Game();
    if (boardFile.is_open()) {
        std::string line;
        Level *level;
        Board *board;
        int nb_obj;
        size_t line_nb = 0;
        while (getline(boardFile, line, '\n')) {
            switch (line[0]) {
                case F_BOARD_SIZE:
                    level = new Level();
                    level = parseLevel(line, &boardFile);
                    game->add_level(level);
                    break;
                case F_NB_OBJ: nb_obj = getNbObj(line); break;
                case F_DIAMOND: addDiamond(level, line); break;
                case F_PLAYER: addPlayer(level, line); break;
                case F_MONSTER: addMonster(level, line); break;
                case F_CHARGER: addCharger(level, line); break;
                case F_DOOR_LINK: addDoorLink(level, line); break;
                case F_LEVEL_LINK: addLevelLink(game, line); break;
                case F_CURRENT_LEVEL: addCurrentLevel(game, line); break;
                case F_PLAYER_STATS: addPlayerStats(game, line); break;
                case F_GAME_STATS: addGameStats(game, line); break;
                case F_COMMENT: break;
                default: break;
            }
        }
        boardFile.close();
        return game;
    } else {
        delete game;
        throw std::invalid_argument("Invalid load file");
    }
    return nullptr;
}

Level *parseLevel(std::string const &line, std::ifstream *boardFile)
{
    std::string delim = " ";
    auto start        = 1U;
    auto end          = line.find(delim);
    std::size_t sizeX = std::stoi(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    std::size_t sizeY = std::stoi(line.substr(start, end - start));
    Board *newBoard;
    newBoard     = new Board(sizeX, sizeY);
    Level *level = new Level();
    level->set_board(newBoard);
    buildBoard(newBoard, boardFile);
    return level;
}

int getNbObj(std::string const &line)
{
    std::string delim = " ";
    auto start        = 2U;
    auto end          = line.find(delim);
    int objects       = std::stoi(line.substr(start, end - start));
    return objects;
}

void addDiamond(Level *&level, std::string const &line)
{
    std::string delim = " ";
    auto start        = 2U;
    auto end          = line.find(delim, start);
    std::size_t x     = std::stoi(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    std::size_t y     = std::stoi(line.substr(start, end - start));
    Diamond *diam     = new Diamond();
    Point2D_u point(x, y);
    level->set_diamond(diam, point, true);
}

void addPlayer(Level *&level, std::string const &line)
{
    std::string delim = " ";
    auto start        = 2U;
    auto end          = line.find(delim, start);
    std::size_t x     = std::stoi(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    std::size_t y     = std::stoi(line.substr(start, end - start));
    Point2D_u point(x, y);
    level->set_player(point);
}

MoveSet *parseMoveSetID(int id)
{
    MoveSet *ms;
    switch (id) {
        case 0:
            ms = new CrossMoveSet();
            return ms;
            break;
        case 1:
            ms = new DiagonalCrossMoveSet();
            return ms;
            break;
        case 2:
            ms = new SquareMoveSet();
            return ms;
            break;
        default: return nullptr; break;
    }
}

AI *parseAI(int id)
{
    switch (id) {
        default:
            AI *ai = new DefaultAI();
            return ai;
            break;
    }
}

void addMonster(Level *&level, std::string const &line)
{
    std::string delim = " ";
    auto start        = 2U;
    auto end          = line.find(delim, start);
    std::size_t x     = std::stoi(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    std::size_t y     = std::stoi(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    Color color       = getMonsterColor(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    int moveSetID     = std::stoi(line.substr(start, end - start));
    MoveSet *moveSet  = parseMoveSetID(moveSetID);
    start             = end + delim.length();
    end               = line.find(delim, start);
    int aiID          = std::stoi(line.substr(start, end - start));
    AI *ai            = parseAI(aiID);
    Monster *monst    = new Monster(ai, moveSet, color);
    Point2D_u point(x, y);
    level->set_monster(monst, point, point, true);
}

Color getMonsterColor(std::string s)
{
    if (s.substr(0, 3) == "MON") {
        int col = std::stoi(s.substr(3, 3));
        switch (col) {
            case 1: return Color::MON1;
            case 2: return Color::MON2;
            case 3: return Color::MON3;
            case 4: return Color::MON4;
            case 5: return Color::MON5;
            case 6: return Color::MON6;
            case 7: return Color::MON7;
            case 8: return Color::MON8;
            case 9: return Color::MON9;
            default: return Color::MON10;
        }
    }
    return Color::UNK;
}

ChargerType parseChargerID(int id)
{
    switch (id) {
        case 0: return ChargerType::RANDOM; break;
        case 1: return ChargerType::RANDOM_SAFE; break;
        default: return ChargerType::NORMAL; break;
    }
}

void addCharger(Level *&level, std::string const &line)
{
    std::string delim = " ";
    auto start        = 2U;
    auto end          = line.find(delim, start);
    std::size_t x     = std::stoi(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    std::size_t y     = std::stoi(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    int chargerTypeID = std::stoi(line.substr(start, end - start));
    ChargerType ct    = parseChargerID(chargerTypeID);
    Charger *c        = new Charger(ct);
    Point2D_u point(x, y);
    level->set_charger(c, point, point, true);
}

void addDoorLink(Level *&level, std::string const &line)
{
    std::string delim  = " ";
    auto start         = 2U;
    auto end           = line.find(delim, start);
    std::size_t x_diam = std::stoi(line.substr(start, end - start));
    start              = end + delim.length();
    end                = line.find(delim, start);
    std::size_t y_diam = std::stoi(line.substr(start, end - start));
    start              = end + delim.length();
    end                = line.find(delim, start);
    std::size_t x_door = std::stoi(line.substr(start, end - start));
    start              = end + delim.length();
    end                = line.find(delim, start);
    std::size_t y_door = std::stoi(line.substr(start, end - start));
    Point2D_u coord_diam(x_diam, y_diam);
    Point2D_u coord_door(x_door, y_door);
    level->set_link(coord_diam, coord_door);
}

void buildBoard(Board *&board, std::ifstream *boardFile)
{
    for (int i = 0; i < board->x(); i++) {
        std::string line;
        getline(*(boardFile), line, '\n');
        for (int j = 0; j < board->y(); j++) {
            Point2D_u coord(i, j);
            switch (line[j]) {
                case SQUARE_WALL:
                    board->set_square(coord, new Square(false, Color::WALL1));
                    break;
                case SQUARE_EMPTY: // No need.
                    break;
                case SQUARE_DOOR_OPEN:
                    board->set_square(i, j, new Door(true));
                    break;
                case SQUARE_DOOR_CLOSED:
                    board->set_square(i, j, new Door(false));
                    break;
                case SQUARE_DOOR_GOAL_OPEN:
                    board->set_square(i, j, new Door(true, true));
                    break;
                case SQUARE_DOOR_GOAL_CLOSED:
                    board->set_square(i, j, new Door(false, true));
                    break;
                default:
                    (board->get_square(coord))->set_color(Color::UNK);
                    break;
            }
        }
    }
}

void addLevelLink(Game *&game, std::string const &line)
{
    std::string delim = " ";
    auto start        = 2U;
    auto end          = line.find(delim, start);
    int id1           = std::stoi(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    int x1            = std::stoi(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    int y1            = std::stoi(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    int id2           = std::stoi(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    int x2            = std::stoi(line.substr(start, end - start));
    start             = end + delim.length();
    end               = line.find(delim, start);
    int y2            = std::stoi(line.substr(start, end - start));
    Point2D_u from_coord(x1, y1);
    Point2D to_coord(x2, y2);
    game->add_link(id1, from_coord, id2, to_coord, false);
}

void addCurrentLevel(Game *&game, std::string const &line)
{
    std::string delim = " ";
    auto start        = 2U;
    auto end          = line.find(delim, start);
    std::size_t level_num
        = (std::size_t)std::stoi(line.substr(start, end - start));
    start = end + delim.length();
    end   = line.find(delim, start);
    int x = std::stoi(line.substr(start, end - start));
    start = end + delim.length();
    end   = line.find(delim, start);
    int y = std::stoi(line.substr(start, end - start));
    Point2D pos(x, y);
    game->set_current_level(level_num);
}

void addPlayerStats(Game *&game, std::string const &line)
{
    std::string delim        = " ";
    auto start               = 2U;
    auto end                 = line.find(delim, start);
    uint charger             = std::stoi(line.substr(start, end - start));
    start                    = end + delim.length();
    end                      = line.find(delim, start);
    uint charger_random      = std::stoi(line.substr(start, end - start));
    start                    = end + delim.length();
    end                      = line.find(delim, start);
    uint charger_safe_random = std::stoi(line.substr(start, end - start));
    start                    = end + delim.length();
    end                      = line.find(delim, start);
    uint diamonds            = std::stoi(line.substr(start, end - start));
    PlayerStats *ps          = new PlayerStats(
        charger, charger_random, charger_safe_random, diamonds);
    game->set_player_stats(ps);
}

void addGameStats(Game *&game, std::string const &line)
{
    std::string delim             = " ";
    auto start                    = 2U;
    auto end                      = line.find(delim, start);
    uint monster_killed           = std::stoi(line.substr(start, end - start));
    start                         = end + delim.length();
    end                           = line.find(delim, start);
    uint died                     = std::stoi(line.substr(start, end - start));
    start                         = end + delim.length();
    end                           = line.find(delim, start);
    uint distance_travelled       = std::stoi(line.substr(start, end - start));
    start                         = end + delim.length();
    end                           = line.find(delim, start);
    uint diamonds_collected       = std::stoi(line.substr(start, end - start));
    start                         = end + delim.length();
    end                           = line.find(delim, start);
    uint changed_level            = std::stoi(line.substr(start, end - start));
    start                         = end + delim.length();
    end                           = line.find(delim, start);
    uint charger_used_total       = std::stoi(line.substr(start, end - start));
    start                         = end + delim.length();
    end                           = line.find(delim, start);
    uint charger_used_normal      = std::stoi(line.substr(start, end - start));
    start                         = end + delim.length();
    end                           = line.find(delim, start);
    uint charger_used_random      = std::stoi(line.substr(start, end - start));
    start                         = end + delim.length();
    end                           = line.find(delim, start);
    uint charger_used_safe_random = std::stoi(line.substr(start, end - start));
    GameStats *gs                 = new GameStats(monster_killed,
                                  died,
                                  distance_travelled,
                                  diamonds_collected,
                                  changed_level,
                                  charger_used_total,
                                  charger_used_normal,
                                  charger_used_random,
                                  charger_used_safe_random);
    game->set_game_stats(gs);
}
