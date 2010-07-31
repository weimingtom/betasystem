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
            m_attack_list[i] = static_cast< AttackType >( i );
        }
        m_select_index = 0 ;
    };
    
public:
    AttackType AttackTypeOf( int index ) const
    {
        return m_attack_list[ index ];
    }
    
public:
    AttackType m_attack_list[ AttackListNum ];
    int m_select_index;
};

#endif // include_21e97407_aadb_4abc_882f_2c4a55ee2b26

