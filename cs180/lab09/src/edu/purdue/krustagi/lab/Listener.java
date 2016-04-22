import android.view.View.*;
import android.view.View;
import java.util.*;
import android.os.*;
import android.widget.*;

public class Listener implements OnClickListener {
    public void onClick(View arg) {
        Button b = (Button) arg;
        if(((b.getText()).toString()).equals("Reset"))
            StartActivity.logIt("This is Reset");
        if(((b.getText()).toString()).equals("Time"))
            StartActivity.logIt("This is Time");
        if(((b.getText()).toString()).equals("Reset"))
            StartActivity.logIt("This is Serial");
    }
    
}