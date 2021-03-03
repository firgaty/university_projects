#ifndef INCLUDE_MODEL_GAMEOBJECT_CHARGER_HPP_
#define INCLUDE_MODEL_GAMEOBJECT_CHARGER_HPP_

#include "GameObject.hpp"
#include "ChargerType.hpp"

class Charger : public virtual GameObject
{
private:
    ChargerType _type;

public:
    Charger(ChargerType type, Color color)
        : GameObject(color, GameObjectType::CHARGER), _type(type)
    {
    }
    Charger(ChargerType type = ChargerType::NORMAL)
        : GameObject(CHARG1, GameObjectType::CHARGER), _type(type)
    {
        switch (type) {
            case ChargerType::NORMAL: set_color(CHARG1); break;
            case ChargerType::RANDOM: set_color(CHARG2); break;
            case ChargerType::RANDOM_SAFE: set_color(CHARG3); break;
            default: set_color(CHARG1);
        };
    }
    ~Charger() {}

    const ChargerType &get_type() const { return _type; }

    void set_charger_type(ChargerType type){
        _type=type;
    };

    static bool is_this_type(const GameObject *o)
    {
        return (dynamic_cast<const Charger *>(o) != nullptr);
    }
};

#endif // !INCLUDE_MODEL_GAMEOBJECT_CHARGER_HPP_