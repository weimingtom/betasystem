#ifndef include_3108f83f_5fbe_43f0_831a_bbfccc61e79a
#define include_3108f83f_5fbe_43f0_831a_bbfccc61e79a

#include "Project/AttackType.hpp"

class CharacterStatus
{
private:
    //! 引数入力を強制させるためデフォルトコンストラクタを非公開に.
    CharacterStatus(){}
    
public:
    CharacterStatus( int hp_max , int attack , int exp );
    
public:
    bool IsLive()  const{ return ( m_hp > 0 ); }
    int AttackDamage() const;
    bool IsDead() const { return ( m_hp <= 0 ); }
    void SetGuard( bool is_guard ) { m_is_guard = is_guard; }
    bool IsGuard() const { return m_is_guard; }
    
public:
    int m_hp_max;
    int m_hp;
    int m_attack;
    int m_exp;
    int m_exp_max;
    bool m_is_guard;
};

#endif //include_3108f83f_5fbe_43f0_831a_bbfccc61e79a

