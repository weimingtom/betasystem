

class PrincessSceneManager extends SceneManagerBase
{
    static final int SceneTitle = 0;
    static final int SceneBattle = 1;
    
    SceneBase new_Scene( int scene_index )
    {
        switch( scene_index )
        {
        case SceneTitle:
            return new SceneTitle( this );
        case SceneBattle:
            return new SceneBattle( this );
        default:
            return null;
        }
    }
}