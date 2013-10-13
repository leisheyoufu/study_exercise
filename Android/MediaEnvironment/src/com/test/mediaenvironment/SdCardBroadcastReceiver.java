package com.test.mediaenvironment;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class SdCardBroadcastReceiver extends BroadcastReceiver {

	
        
    
      
 
  
      
	
	@Override
	public void onReceive(Context context, Intent intent) {
		// TODO Auto-generated method stub
		Log.i("Sdcard","receiver");
		String action = intent.getAction();
		// 当插上USB后启动UsbStorageActivity
		if (action.equals(Intent.ACTION_UMS_DISCONNECTED)) {
			Log.i("Sdcard","mounted");
			final Intent mIntent = new Intent();
			mIntent.setClass(context, MediaEnvironmentActivity.class);
			mIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			context.startActivity(mIntent);
	    
		}

	}
}
