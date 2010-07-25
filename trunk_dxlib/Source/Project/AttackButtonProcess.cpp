#include "System/ProcessBase.hpp"
#include "Project/AttackButtonProcess.hpp"
#include "Project/AttackContent.hpp"

class AttackButtonProcess : public ProcessBase
{
public:
    AttackButtonProcess( int index , AttackContent& attack_content );
    ~AttackButtonProcess();
public:
    void Run();
    
private:
    int const m_index;
    AttackContent& m_attack_content;
};

AttackButtonProcess::AttackButtonProcess( int index , AttackContent& attack_content )
 : m_index( index )
 , m_attack_content( attack_content )
{
}

AttackButtonProcess::~AttackButtonProcess()
{
}

void AttackButtonProcess::Run()
{
    m_attack_content.m_select_index = m_index;
}

ProcessBase* new_AttackButtonProcess( int index , AttackContent& attack_content )
{
    return new AttackButtonProcess( index , attack_content );
}


