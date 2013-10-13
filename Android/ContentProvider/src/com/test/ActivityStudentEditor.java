package com.test;

import com.test.util.FullScreenUtil;

import android.app.Activity;
import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.BaseColumns;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;



public class ActivityStudentEditor extends Activity {
	private static final String TAG = "Diary";
	public static final String EDIT_STUDENT_ACTION = "com.test.ActivityStudentEditor.EDIT_STUDENT";
	public static final String INSERT_STUDENT_ACTION = "com.test.ActivityStudentEditor.INSERT_STUDENT";

	public static final String AUTHORITY = "com.test.scucontentprovider";
	public static final String DEFAULT_SORT_ORDER = "age DESC";
	public static final String CONTENT_TYPE = "vnd.android.cursor.dir/vnd.google.student";
    public static final String CONTENT_ITEM_TYPE = "vnd.android.cursor.item/vnd.google.student";
    public static final Uri CONTENT_URI = Uri.parse("content://" + AUTHORITY + "/student");
	private static final String DATABASE_NAME = "scu";
	private static final int DATABASE_VERSION = 3;
	private static final String STUDENT_TABLE_NAME = "student";

	private static final int STUDENT = 1;
	private static final int STUDENT_ID = 2;
	
	
	
	/**
	 * 查询cursor时候，感兴趣的那些条例。
	 */
	private static final String[] PROJECTION = new String[] { BaseColumns._ID, // 0
			"name", "age", // 1
	};

	private static final int STATE_EDIT = 0;
	private static final int STATE_INSERT = 1;

	private int mState;

	private Uri mUri;
	private Cursor mCursor;

	private EditText mNameText;
	private EditText mageText;
	private Button confirmButton;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		FullScreenUtil.hideTitle(this);
		FullScreenUtil.hideStatusBar(this);
		
		
		setTheme(android.R.style.Theme_Black);
		final Intent intent = getIntent();
		final String action = intent.getAction();
		setContentView(R.layout.student_edit);
		
		mNameText = (EditText) findViewById(R.id.name);
		mageText = (EditText) findViewById(R.id.age);
		confirmButton = (Button) findViewById(R.id.confirm);

		if (EDIT_STUDENT_ACTION.equals(action)) {// 编辑
			mState = STATE_EDIT;
			mUri = intent.getData();
			
			mCursor = managedQuery(mUri, PROJECTION, null, null, null);
			mCursor.moveToFirst();
			String name = mCursor.getString(1);
			mNameText.setTextKeepState(name);
			String age = mCursor.getString(2);
			mageText.setTextKeepState(age);
			setResult(RESULT_OK, (new Intent()).setAction(mUri.toString()));
			setTitle("编辑");
		} else if (INSERT_STUDENT_ACTION.equals(action)) {// 新建
			mState = STATE_INSERT;
			setTitle("新建");
		} else {
			Log.e(TAG, "no such action error");
			finish();
			return;
		}

		confirmButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				if (mState == STATE_INSERT) {
					insertDiary();
				} else {
					updateDiary();
				}
				Intent mIntent = new Intent();
				setResult(RESULT_OK, mIntent);
				finish();
			}

		});

	}

	private void insertDiary() {
		String name = mNameText.getText().toString();
		String age = mageText.getText().toString();
		ContentValues values = new ContentValues();
		
		values.put("name", name);
		values.put("age", age);
		getContentResolver().insert(CONTENT_URI, values);

	}

	private void updateDiary() {
		String name = mNameText.getText().toString();
		String age = mageText.getText().toString();
		ContentValues values = new ContentValues();
	
		values.put("name", name);
		values.put("age", age);
		getContentResolver().update(mUri, values,
				null, null);

	}
}
