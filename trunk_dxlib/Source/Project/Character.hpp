#ifndef include_3108f83f_5fbe_43f0_831a_bbfccc61e79a
#define include_3108f83f_5fbe_43f0_831a_bbfccc61e79a

#include "Project/AttackType.hpp"

class Character
{
private:
    //! 適切に生成されるよう、引数を強制するためデフォルトコンストラクタを非公開に.
    Character(){}
    
public:
    Character( int hp_max , int attack , int exp );

public:
    int m_hp;
    int m_hp_max;
    int m_attack;
    int m_exp;
    static int const m_exp_max = 100;
};

#endif

