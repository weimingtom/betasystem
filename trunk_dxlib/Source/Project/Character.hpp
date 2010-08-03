#ifndef include_3108f83f_5fbe_43f0_831a_bbfccc61e79a
#define include_3108f83f_5fbe_43f0_831a_bbfccc61e79a

#include "Project/AttackType.hpp"

class Character
{
private:
    //! �K�؂ɐ��������悤�A�������������邽�߃f�t�H���g�R���X�g���N�^�����J��.
    Character(){}
    
public:
    //! ���x���P�̎��̃X�e�[�^�X�w�肷��.
    Character( int hp_max , int attack , int exp );

public:
    void UpLevel();
    void SetLevel( int level );
    bool CanUpLevel() const;

public:
    int m_level;
    int m_hp_max;
    int m_hp;
    int m_attack;
    int m_exp;
};

#endif

