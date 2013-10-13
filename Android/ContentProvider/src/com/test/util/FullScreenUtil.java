package com.test.util;

import android.app.Activity;
import android.view.Window;
import android.view.WindowManager;

public class FullScreenUtil {
	public static void hideTitle(Activity activity)
	{
		activity.requestWindowFeature(Window.FEATURE_NO_TITLE);
	}
	
	public static void hideStatusBar(Activity activity)
	{
		int flag=WindowManager.LayoutParams.FLAG_FULLSCREEN;
		Window myWindow = activity.getWindow();
		myWindow.setFlags(flag, flag);
	}

}
