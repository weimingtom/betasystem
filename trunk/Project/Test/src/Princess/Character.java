
/**
    キャラクター情報を保持するクラス.
*/
class Character
{
    String m_name;
    int m_hp;
    int m_hp_max;
    int m_attack;
    int m_exp; //!< 経験値.
    final int m_exp_max = 10 ;
    final float m_grow_persent = 1.7f; //!< 成長係数.
    
    Character( String name , int hp_max , int attack , int exp )
    {
        m_name = name ;
        m_hp_max = hp_max ;
        m_attack = attack ;
        m_exp = exp;
        
        FullRecovery();
    }
    
    void FullRecovery()
    {
        m_hp = m_hp_max;
    }
    
    void LevelUp()
    {
        while( m_exp >= m_exp_max )
        {
            m_hp_max *= m_grow_persent;
            m_attack *= m_grow_persent;
            m_exp -= m_exp_max;
            FullRecovery();
        }
    }
};

