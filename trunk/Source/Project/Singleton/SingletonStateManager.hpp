#ifndef PRINCESS_SOURCE_PROJECT_SINGLETON_SINGLETONSTATEMANAGER
#define PRINCESS_SOURCE_PROJECT_SINGLETON_SINGLETONSTATEMANAGER

#include <string>
#include <memory>
#include "System/Statebase.hpp"

namespace Princess
{
    //! ステート.
    enum State{
        State_DebugTop,     //!< デバッグトップ.
        State_Action,       //!< アクションテスト.
        State_LuaTest,      //!< luaテスト.
        State_DrawTexture,  //!< 画像描画テスト.
        State_CreateChara,  //!< キャラ生成.
        State_Num,
    };

	/**
	    プロジェクトの一番上に位置するStateManager.
	*/
	class StateManager
	{
	public:
	    //! デストラクタ.
	    ~StateManager();

	public:
	    //! ステートマネージャのポインタ取得.
	    static StateManager* GetInstance();

	    //! インスタンスの削除.
	    static void DeleteInstance();

	    //! ステートインスタンスの生成.
	    //! @param state 生成したいステートの種類.
	    static StateBase* new_State(State state);

	    //! 名前の取得.
	    static std::string NameOf(State state);

	public:
	    /**
	        遷移切り替え.インスタンスの管理はこのクラスがやる.
	        @param next_state 切り替えるStateのポインタ.
	    */
	    void ChangeState( StateBase* next_state )
	    {
	        m_next_state.reset( next_state );
	    }
	    /**
	        更新.
	    */
	    void Update()
	    {
	        if( m_next_state.get() )
	        {
	            m_current_state.reset( m_next_state.release() );
	        }
	        m_current_state->Update();
	    }
	    /**
	        描画.
	    */
	    void Draw()
	    {
	        m_current_state->Draw();
	    }

	private:
	    //! コンストラクタ.
	    StateManager();
	    
	private:
	    std::auto_ptr< StateBase > m_current_state;
	    std::auto_ptr< StateBase > m_next_state;
	};

} // end of namespace Princess

#endif // PRINCESS_SOURCE_PROJECT_SINGLETON_SINGLETONSTATEMANAGER

