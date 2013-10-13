package com.test.scantfcard;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;



import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

public class TFStartService extends Service {
    private static final String TAG = "cl BroadCastTest";

    BroadcastReceiver mReceiver;
    private int tfIn;
    private boolean boot;
    private Handler handler;
	private Runnable runnable;

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    public void onCreate() {
        super.onCreate();
        tfIn = 0;
        boot = true;
    
        Log.d(TAG, "oncreate");
    }

    public void onStart(Intent intent, int startId) {
        Log.d(TAG, "onstart");
    
        mReceiver = new BroadcastReceiver() {
            public void onReceive(Context context, Intent intent) {
            	if(intent != null && intent.getExtras()!=null &&intent.getExtras().get("boot") != null)
            	{
            		boot = intent.getExtras().getBoolean("boot");
            	}
                if (intent.getAction().equals(Intent.ACTION_MEDIA_MOUNTED)) {
                	if(!isExternalSdMount())
                	{
                		tfIn = 1;
                		Log.i(TAG,"No TF Card");
                		if(boot == true)
                		{
                    		handler = new Handler();
                    		runnable = new Runnable() {
                				public void run() {
                					boot = false;
                					Log.i(TAG,"TF Card runner");
                				}
                			};
                			handler.postDelayed(runnable, 100000);
                		}
                	
                	}
                	else if(tfIn == 1 && isExternalSdMount()&& !boot)
                	{
                		tfIn = 2;
                		boot = false;
                		Log.i(TAG,"Insert TF Card after boot");
                	}
           
                } 
                
                if(intent.getAction().equals(Intent.ACTION_MEDIA_EJECT))
                {
                	tfIn = 1;
                	boot = false;
                	Log.i(TAG,"TF Card eject");
                }
            }
        };
        // Fileter for SDCard mounted and unmounted
        IntentFilter filterTFCard = new IntentFilter();
        filterTFCard.addAction(Intent.ACTION_MEDIA_MOUNTED);
        filterTFCard.addAction(Intent.ACTION_MEDIA_CHECKING);
        filterTFCard.addAction(Intent.ACTION_MEDIA_NOFS);
        filterTFCard.addAction(Intent.ACTION_MEDIA_EJECT);
        filterTFCard.addAction(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE);
        filterTFCard.addAction(Intent.ACTION_MEDIA_SCANNER_STARTED);
        filterTFCard.setPriority(1000);
     
        filterTFCard.addDataScheme("file");
        registerReceiver(mReceiver, filterTFCard);


    }
    
    /* ÷¥––√¸¡Ó */
    private String execCMD(String cmd,String[]para)
    {
    	try {
    		Process process=Runtime.getRuntime().exec(cmd);
            BufferedReader br=new BufferedReader(new InputStreamReader(process.getInputStream())); 
            String str ="";
            char []b= new char[1024];
            
            while(br.read(b)!=-1)
            {
            	str +=str.copyValueOf(b);
            }
          
            return str;
            	
        } catch (IOException e) { 
            // TODO Auto-generated catch block 
            Log.d(TAG, e.getMessage()); 
            e.printStackTrace();
        }
    	return null;
    	
    }
    /* Ω‚Œˆ√¸¡Ó */
    private String resolveCMD(String cmdReturnStr,String CMD,String para)
    {
    	if(CMD.equals("df"))
    	{
    		int index = 0;
    		String mountPaths = null;
    		
    		
    		String temp[] = cmdReturnStr.split(" ");
    		for(int i=0;i<temp.length;i++)
    		{
    			if(temp[i].contains("external_sd")) //≈–∂œ «∑Ò¥Ê‘⁄Õ‚÷√sdø®µƒπ“‘ÿ¬∑æ∂
    			{
    				return temp[i];
    				
    			}
    		}
    	}
    	return null;
    }
    
    public String getMountPaths()
    {
    	
    	String cmdReturnStr = execCMD("df",null);
    	return resolveCMD(cmdReturnStr,"df",null);
    }
    
    public boolean isExternalSdMount()
    {
    	String cmdReturnStr = execCMD("df",null);
    	if(resolveCMD(cmdReturnStr,"df",null) !=null)
    	{
    		return true;
    	}
    	return false;
    }
}

