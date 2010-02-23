import com.nttdocomo.ui.IApplication;
import com.nttdocomo.ui.Canvas;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Frame;
import com.nttdocomo.ui.Display;

public class Test extends IApplication
{
    public void start()
    {
        MainCanvas main_canvas = new MainCanvas();
        Display.setCurrent( ( Frame )( main_canvas ) );
        Thread th = new Thread( main_canvas );
        th.start();
    }
}

