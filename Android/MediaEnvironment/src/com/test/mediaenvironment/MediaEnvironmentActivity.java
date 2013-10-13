package com.test.mediaenvironment;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;

public class MediaEnvironmentActivity extends Activity {
    /** Called when the activity is first created. */
	
    
    private final BroadcastReceiver sdcardListener=new BroadcastReceiver()
    {
    	 @Override  
    	public void onReceive(Context context, Intent intent)
    	{
    		Log.i("cl sdcard","reciever");
    		Log.i("cl Environment mounted",Environment.MEDIA_MOUNTED);
    		
    		Log.i("cl Environment state",Environment.getExternalStorageState());
    		
    		Log.i("cl Environment directory",Environment.getExternalStorageDirectory().getAbsolutePath());
    	}
    };
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
  
        
        
    
		Log.i("external sd card removeable",String.valueOf(Environment.isExternalStorageRemovable()));
		
		Log.i("external directory",String.valueOf(Environment.getExternalStorageDirectory()));
		try {
		Process process=Runtime.getRuntime().exec("df");
		
        BufferedReader br=new BufferedReader(new InputStreamReader(process.getInputStream())); 
        String str; 
        while((str=br.readLine())!= null) Log.i("testsd",str); 
    } catch (IOException e) { 
        // TODO Auto-generated catch block 
        Log.i("testsd", e.getMessage()); 
        e.printStackTrace();

   }
    }
    
    @Override  
    protected void onStart() {  
        // TODO Auto-generated method stub  
        super.onStart();  
            IntentFilter intentFilter = new IntentFilter();  
            intentFilter.addAction(Intent.ACTION_MEDIA_UNMOUNTED);  
            intentFilter.addAction(Intent.ACTION_MEDIA_EJECT);  
            intentFilter.addAction(Intent.ACTION_MEDIA_REMOVED);  
            intentFilter.addAction(Intent.ACTION_MEDIA_BAD_REMOVAL);  
            intentFilter.addAction(Intent.ACTION_MEDIA_SCANNER_FINISHED);  
            intentFilter.addDataScheme("file");  
            registerReceiver(sdcardListener, intentFilter);  
    }  
      
    @Override  
    protected void onStop() {  
        // TODO Auto-generated method stub  
        super.onStop();  
        unregisterReceiver(sdcardListener);  
    }  
}