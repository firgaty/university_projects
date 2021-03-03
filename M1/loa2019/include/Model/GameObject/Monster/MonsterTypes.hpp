#include "Model/AI/DefaultAI.hpp"
#include "Model/GameObject/Monster/Monster.hpp"
#include "Model/MoveSet/SquareMoveSet.hpp"

class MonsterDefault : virtual public Monster
{
public:
    MonsterDefault()
        : Monster(new DefaultAI(), new SquareMoveSet(), Color::MON1){};
};