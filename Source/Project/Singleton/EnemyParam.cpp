#include "EnemyParam.hpp"

EnemyParam gEnemyParam;

EnemyParam EnemyParamOf(EnemyID enemy_id)
{
    EnemyParam const enemy_list[] =
    {
        //hp,attack,{id,color,level}
        {
            10,4,
            {
                {Item_Hair0,    1,0x0011FF11,0,EquipPos_Hair},
                {Item_Cloth1,   1,0,0,EquipPos_Body},
            },
        },
        //hp,attack,equip
        {
            10,4,
            {
                {Item_Hair0,    0,0,0,EquipPos_Hair},
                {Item_Cloth1,    0,0,0,EquipPos_Body},
            },
        },
        //hp,attack,equip
        {
            10,4,
            {
                {Item_Hair0,    0,0,0,EquipPos_Hair},
                {Item_Cloth1,    0,0,0,EquipPos_Body},
            },
        },
    };

    return enemy_list[enemy_id];
}

