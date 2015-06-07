#ifndef STATE_DEBUG_TOP__
#define STATE_DEBUG_TOP__

#include <vector>
#include "System/StateBase.hpp"
#include "Project/Singleton/SingletonStateManager.hpp"

namespace Game
{
	class StateDebugTop : public StateBase
	{
	public:
	    StateDebugTop();
	    ~StateDebugTop(){}
	public:
	    void Update();
	    void Draw();
	private:
	    int mIndex;
	    std::vector<State> m_StateList;
	};

} // namespace Game

#endif // STATE_DEBUG_TOP__

