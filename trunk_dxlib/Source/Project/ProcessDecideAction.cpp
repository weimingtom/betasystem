#include "System/ProcessBase.hpp"
#include "Project/ProcessDecideAction.hpp"
#include "Project/Character.hpp"

class ProcessDecideAction : public ProcessBase
{
public:
    ProcessDecideAction(
        int index ,
        Character& character );
    ~ProcessDecideAction();
public:
    void Run();
    bool CanRunning();
    
private:
    int const m_index;
    Character& m_character;
};

ProcessDecideAction::ProcessDecideAction(
    int index ,
    Character& character )
 : m_index( index )
 , m_character( character )
{
}

ProcessDecideAction::~ProcessDecideAction()
{
}

void ProcessDecideAction::Run()
{
    m_character.m_select_index = m_index;
}

bool ProcessDecideAction::CanRunning()
{
    AttackType const attack_type = m_character.m_attack_list[ m_index ];
    
    return ( NeedPointOf( attack_type ) <= m_character.m_action_point );
}

ProcessBase* new_ProcessDecideAction( int index , Character& character )
{
    return new ProcessDecideAction( index , character );
}


