package com.test.scantfcard;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class ScanTFCardActivity extends Activity {
    /** Called when the activity is first created. */
	
	static final String BOOTCOMPLETEDACTION = "com.android.action.BOOTCOMPLETEDACTION";
	private TextView tv;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.main);
   
    }
}