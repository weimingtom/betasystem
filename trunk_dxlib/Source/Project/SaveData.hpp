#ifndef include_6227f8ae_11de_44fc_ae49_2133fed65c60
#define include_6227f8ae_11de_44fc_ae49_2133fed65c60

#include "Project/Character.hpp"

class SaveData
{
public:
    static SaveData& GetInstance();
private:
    SaveData();
public:
    Character m_player_status;
};

#endif
