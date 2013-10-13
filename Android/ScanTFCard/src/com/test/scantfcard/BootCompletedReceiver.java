package com.test.scantfcard;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

public class BootCompletedReceiver extends BroadcastReceiver {
	Context context;
	//private boolean boot = false;
	static private String Tag = "cl BootCompleteReceiver ";

	@Override
	public void onReceive(Context context, Intent intent) {
		this.context = context;

		String action = intent.getAction();
		if (action.equals(Intent.ACTION_BOOT_COMPLETED)) {
			Intent mintent=new Intent("com.test.scantfcard.TFStartService");
		
			Bundle extras = new Bundle();
			extras.putBoolean("boot", true);
			mintent.putExtras(extras);
			
			 context.startService(mintent);
		
			// context.startActivity(myintent);
		//	boot = true;
			// Toast.makeText(context, "¿ª»úÀ² ....", Toast.LENGTH_SHORT).show();
			Log.d(Tag, "Booting ");

		}
	}

}
