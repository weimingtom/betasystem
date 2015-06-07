#ifndef PRINCESS_SOURCE_PROJECT_STATE_STATESUSHI
#define PRINCESS_SOURCE_PROJECT_STATE_STATESUSHI

#include <vector>
#include "System/StateBase.hpp"
#include "Project/Singleton/SingletonStateManager.hpp"

namespace Game
{
	class StateSushi : public StateBase
	{
	public:
	    StateSushi();
	    ~StateSushi(){}
	public:
	    void Update();
	    void Draw();
	};

} // namespace Princess

#endif // PRINCESS_SOURCE_PROJECT_STATE_STATESUSHI

