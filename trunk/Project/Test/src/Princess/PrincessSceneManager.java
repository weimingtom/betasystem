
/**
    Princess�ɂ������ʑJ�ڂ��Ǘ�����N���X.
*/
class PrincessSceneManager extends SceneManagerBase
{
    static final int SceneTitle = 0;
    static final int SceneWorldMap = 1;
    static final int SceneBattle = 2;
    
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
        default:
            return null;
        }
    }
}