#include "System/ProcessBase.hpp"
#include "Project/ProcessDecideAction.hpp"
#include "Project/AttackContent.hpp"
#include "Project/Character.hpp"

class ProcessDecideAction : public ProcessBase
{
public:
    ProcessDecideAction(
        int index ,
        AttackContent& attack_content ,
        Character const& character );
    ~ProcessDecideAction();
public:
    void Run();
    bool CanRunning();
    
private:
    int const m_index;
    AttackContent& m_attack_content;
    Character const m_character;
};

ProcessDecideAction::ProcessDecideAction(
    int index ,
    AttackContent& attack_content ,
    Character const& character )
 : m_index( index )
 , m_attack_content( attack_content )
 , m_character( character )
{

}

ProcessDecideAction::~ProcessDecideAction()
{
}

void ProcessDecideAction::Run()
{
    m_attack_content.m_select_index = m_index;
}

bool ProcessDecideAction::CanRunning()
{
    AttackType const attack_type = m_attack_content.m_attack_list[ m_index ];
    
    return ( NeedPointOf( attack_type ) <= m_character.m_action_point );
}

ProcessBase* new_ProcessDecideAction( int index , AttackContent& attack_content , Character const& character )
{
    return new ProcessDecideAction( index , attack_content , character );
}


