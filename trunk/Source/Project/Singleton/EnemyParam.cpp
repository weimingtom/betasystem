#include "EnemyParam.hpp"

EnemyParam gEnemyParam;

EnemyParam EnemyParamOf(EnemyID enemy_id)
{
    EnemyParam const enemy_list[] =
    {
        //hp,attack,equip
        {
            10,4,
            {
                {Item_Hair0,    0,0,0,EquipPos_Hair},
                {Item_Hair0,    0,0,0,EquipPos_Hair},
            },
        },
        //hp,attack,equip
        {
            10,4,
            {
                {Item_Hair0,    0,0,0,EquipPos_Hair},
                {Item_Hair0,    0,0,0,EquipPos_Hair},
            },
        },
        //hp,attack,equip
        {
            10,4,
            {
                {Item_Hair0,    0,0,0,EquipPos_Hair},
                {Item_Hair0,    0,0,0,EquipPos_Hair},
            },
        },
    };

    return enemy_list[enemy_id];
}

