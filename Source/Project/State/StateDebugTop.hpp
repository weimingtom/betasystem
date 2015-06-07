#ifndef STATE_DEBUG_TOP__
#define STATE_DEBUG_TOP__

#include <vector>
#include "System/StateBase.hpp"
#include "Project/Singleton/SingletonStateManager.hpp"

namespace Princess
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

} // namespace Princess

#endif // STATE_DEBUG_TOP__

