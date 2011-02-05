#ifndef include_guard_dab9ac90_e1c4_4e8c_bed1_df0275db9b24
#define include_guard_dab9ac90_e1c4_4e8c_bed1_df0275db9b24

class StateManagerBase;
#include "System/StateBase.hpp"

class StateBattle : public StateBase
{
public:
    StateBattle( StateManagerBase& manager );
    
public:
    void Update();
    void Draw();

private:
	void UpdateMeter();
	void DecideMeter();
	
private:
    StateManagerBase& m_manager;
    int m_meter;
    int m_add_meter;
};

#endif

