import com.nttdocomo.ui.Canvas;

/**
    基本遷移となるクラス.
*/
abstract class SceneBase extends Canvas
{
    abstract void Init();
    abstract void Update();
    abstract void Draw();
}
