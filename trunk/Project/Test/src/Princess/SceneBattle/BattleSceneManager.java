/**
    í“¬‰æ–Ê‚É‚¨‚¯‚é‰æ–Ê‘JˆÚŠÇ—.
*/
class BattleSceneManager extends SceneManagerBase
{
    static final int Scene_PlayerTurn  = 0;
    static final int Scene_EnemyTurn   = 1;
    static final int Scene_Win         = 2;
    static final int Scene_Lose        = 3;
    
    SceneBattleObjects m_objects;
    
    BattleSceneManager( SceneManagerBase princess_scene_manager )
    {
        m_objects = new SceneBattleObjects( this , princess_scene_manager );
    }
    
    SceneBase new_Scene( int scene_index )
    {
        switch( scene_index )
        {
        case Scene_PlayerTurn:
            return new ScenePlayerTurn( this , m_objects );
        case Scene_EnemyTurn:
            return new SceneEnemyTurn( this , m_objects );
        case Scene_Win:
            return new SceneWin( this , m_objects );
        case Scene_Lose:
            return new SceneLose( this , m_objects );
        default:
            System.out.println("scene_index is invalid.");
            return null;
        }
    }
}