#ifndef include_guard_uuid_30c54c41_0c5c_48d3_8c5b_ebf1375379ac
#define include_guard_uuid_30c54c41_0c5c_48d3_8c5b_ebf1375379ac

enum AttackType
{
    AttackType_Normal,
    AttackType_Special,
    AttackType_Guard,
    
    AttackType_Num,
};

char const* NameOf( AttackType type );

int NeedPointOf( AttackType attack_type );

#endif

