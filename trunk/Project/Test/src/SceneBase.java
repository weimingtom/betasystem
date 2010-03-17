import com.nttdocomo.ui.Canvas;

/**
    Šî–{‘JˆÚ‚Æ‚È‚éƒNƒ‰ƒX.
*/
abstract class SceneBase extends Canvas
{
    SceneManagerBase m_scene_manager;
    
    SceneBase( SceneManagerBase scene_manager )
    {
        m_scene_manager = scene_manager;
    }
    
    abstract void Init();
    abstract void Update();
    abstract void Draw();
}
