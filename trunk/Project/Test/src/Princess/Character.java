
/**
    キャラクター情報を保持するクラス.
*/
class Character
{
    String m_name;
    int m_hp;
    int m_attack;
    int m_exp; //!< 経験値.
    

    Character( String name , int hp , int attack , int exp )
    {
        m_name = name ;
        m_hp = hp ;
        m_attack = attack ;
        m_exp = exp;
    }
};

