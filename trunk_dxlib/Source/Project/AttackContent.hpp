#ifndef include_21e97407_aadb_4abc_882f_2c4a55ee2b26
#define include_21e97407_aadb_4abc_882f_2c4a55ee2b26

#include "DxLibWrapper/Random.hpp"
#include "Project/AttackType.hpp"

/**
    攻撃行動に関しての情報を保持するクラス.
*/
class AttackContent
{
public:
    static int const AttackListNum = 3;
public:
    AttackContent()
    {
        for( int i = 0 ; i < AttackType_Num ; i++ )
        {
            m_attack_list[i] = static_cast< AttackType >( i );
        }
        m_attack_next = DistributeAttackType();
        m_select_index = 0 ;
    };
    
public:
    AttackType AttackTypeOf( int index ) const
    {
        return m_attack_list[ index ];
    }
    AttackType PopAttack( int index )
    {
        AttackType const result = m_attack_list[index];
        m_attack_list[index] = m_attack_next;
        m_attack_next = DistributeAttackType();
        return result;
    }
private:
    AttackType DistributeAttackType()
    {
        return static_cast< AttackType >( GetRandToMax( AttackType_Num ) );
    }
public:
    AttackType m_attack_list[ AttackListNum ];
    AttackType m_attack_next;
    int m_select_index;
};

#endif // include_21e97407_aadb_4abc_882f_2c4a55ee2b26

