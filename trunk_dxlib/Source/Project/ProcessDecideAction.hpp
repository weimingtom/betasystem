#ifndef include_c6be4de0_40f2_4bed_ade2_320e38f34aae
#define include_c6be4de0_40f2_4bed_ade2_320e38f34aae

class ProcessBase;
class AttackContent;
class Character;

ProcessBase* new_ProcessDecideAction(
    int index ,
    AttackContent& attack_content ,
    Character const& character );

#endif

