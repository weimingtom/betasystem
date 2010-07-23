#ifndef include_21e97407_aadb_4abc_882f_2c4a55ee2b26
#define include_21e97407_aadb_4abc_882f_2c4a55ee2b26

#include "DxLibWrapper/Random.hpp"
#include "Project/AttackType.hpp"

/**
    UŒ‚s“®‚ÉŠÖ‚µ‚Ä‚Ìî•ñ‚ğ•Û‚·‚éƒNƒ‰ƒX.
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
            m_attack[i] = static_cast< AttackType >( i );
        }
        m_attack_next = DistributeAttackType();
    };
    
public:
    AttackType AttackTypeOf( int index ) const
    {
        return m_attack[ index ];
    }
    AttackType PopAttack( int index )
    {
        AttackType const result = m_attack[index];
        m_attack[index] = m_attack_next;
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
};

#endif // include_21e97407_aadb_4abc_882f_2c4a55ee2b26

