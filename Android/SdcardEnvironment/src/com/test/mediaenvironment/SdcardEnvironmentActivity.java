package com.test.mediaenvironment;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;

public class SdcardEnvironmentActivity extends Activity {
    /** Called when the activity is first created. */
	
	private String Tag = "SdcardEnvironment";
    
    private  BroadcastReceiver sdcardListener=new BroadcastReceiver()
    {
    	 @Override  
    	public void onReceive(Context context, Intent intent)
    	{
    		 if(intent.getAction().equals(Intent.ACTION_MEDIA_MOUNTED))
    		 {
    			 Log.i(Tag,"Mouted Path= " +getMountPaths().trim()); 
    		 }
    	}
    };
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        Log.i(Tag,"Activity Started");
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
            intentFilter.addAction(Intent.ACTION_MEDIA_MOUNTED);
            intentFilter.addDataScheme("file");  
            registerReceiver(sdcardListener, intentFilter);  
    }  
      
    @Override  
    protected void onStop() {  
        // TODO Auto-generated method stub  
        super.onStop();  
        unregisterReceiver(sdcardListener);  
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
            Log.i(Tag, e.getMessage()); 
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