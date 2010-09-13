#ifndef include_3108f83f_5fbe_43f0_831a_bbfccc61e79a
#define include_3108f83f_5fbe_43f0_831a_bbfccc61e79a

#include "Project/AttackType.hpp"

class Character
{
private:
    //! �������͂����������邽�߃f�t�H���g�R���X�g���N�^�����J��.
    Character(){}
    
public:
    Character( int hp_max , int attack , int exp );
    
public:
    bool IsLive() const;
    AttackType AttackTypeOf( int index ) const;
    int AttackDamage() const;
    bool IsDead() const { return ( m_hp <= 0 ); }

public:
    static int const AttackListNum = 3;
public:
    int m_hp_max;
    int m_hp;
    int m_attack;
    int m_exp;
    int m_exp_max;
    int m_action_point; // �s���|�C���g.
    int m_action_point_max;
    AttackType m_attack_list[ AttackListNum ];
    int m_select_index;
};

#endif //include_3108f83f_5fbe_43f0_831a_bbfccc61e79a

