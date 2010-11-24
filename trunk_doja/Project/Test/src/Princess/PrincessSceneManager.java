
/**
    Princess‚É‚¨‚¯‚é‰æ–Ê‘JˆÚ‚ğŠÇ—‚·‚éƒNƒ‰ƒX.
*/
class PrincessSceneManager extends SceneManagerBase
{
    static final int SceneTitle = 0;
    static final int SceneWorldMap = 1;
    static final int SceneBattle = 2;
    static final int SceneGameOver = 3;
    
    SceneBase new_Scene( int scene_index )
    {
        switch( scene_index )
        {
        case SceneTitle:
            return new SceneTitle( this );
        case SceneWorldMap:
            return new SceneWorldMap( this );
        case SceneBattle:
            return new SceneBattle( this );
        case SceneGameOver:
            return new SceneGameOver( this );
        default:
            return null;
        }
    }
}