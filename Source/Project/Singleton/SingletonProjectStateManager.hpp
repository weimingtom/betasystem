#ifndef include_4043f656_29d2_4fa5_b7b8_641d2d447994
#define include_4043f656_29d2_4fa5_b7b8_641d2d447994

#include "../../System/StateManagerBase.hpp"

/**
    プロジェクトの一番上に位置するStateManager.
*/
class SingletonProjectStateManager : public StateManagerBase
{
public:
    //! ステート.
    enum State{
        State_DebugTop,
        State_Title,
        State_Num,
    };
public:
    //! デストラクタ.
    ~SingletonProjectStateManager();
public:
    //! ステートマネージャのポインタ取得.
    static SingletonProjectStateManager* GetInstance();
    //! ステートインスタンスの生成.
    //! @param state 生成したいステートの種類.
    static StateBase* new_State(State state);
private:
    //! コンストラクタ.
    SingletonProjectStateManager();
};

#endif

