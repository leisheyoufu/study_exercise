package com.test;

import com.test.util.FullScreenUtil;

import android.app.ListActivity;
import android.content.ContentUris;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.BaseColumns;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;



public class ActivityMain extends ListActivity {
	
	public static final String AUTHORITY = "com.test.scucontentprovider";
	public static final String DEFAULT_SORT_ORDER = "age DESC";
	public static final String CONTENT_TYPE = "vnd.android.cursor.dir/vnd.google.student";
    public static final String CONTENT_ITEM_TYPE = "vnd.android.cursor.item/vnd.google.student";
    public static final Uri CONTENT_URI = Uri.parse("content://" + AUTHORITY + "/student");
	private static final String DATABASE_NAME = "scu";
	private static final int DATABASE_VERSION = 3;
	private static final String STUDENT_TABLE_NAME = "student";
	public static final String EDIT_STUDENT_ACTION = "com.test.ActivityStudentEditor.EDIT_STUDENT";
	public static final String INSERT_STUDENT_ACTION = "com.test.ActivityStudentEditor.INSERT_STUDENT";

	private static final int STUDENT = 1;
	private static final int STUDENT_ID = 2;
	

	// 插入一条新纪录
	public static final int MENU_ITEM_INSERT = Menu.FIRST;
	// 编辑内容
	public static final int MENU_ITEM_EDIT = Menu.FIRST + 1;
	public static final int MENU_ITEM_DELETE = Menu.FIRST + 2;

	private static final String[] PROJECTION = new String[] { BaseColumns._ID,
			"name", "age" };

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		FullScreenUtil.hideTitle(this);
		FullScreenUtil.hideStatusBar(this);
		
		setContentView(R.layout.student_list);
		Intent intent = getIntent();
		if (intent.getData() == null) {
			intent.setData(CONTENT_URI);
		}
		Log.i("cl","CONTENT_URI"+CONTENT_URI.getAuthority());
		
		Cursor cursor = managedQuery(getIntent().getData(), PROJECTION, null,
				null, "age DESC");

		SimpleCursorAdapter adapter = new SimpleCursorAdapter(this,
				R.layout.student_row, cursor, new String[] { "name",
						"age" }, new int[] { R.id.name,
						R.id.age });
		setListAdapter(adapter);
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		menu.add(0, MENU_ITEM_INSERT, 0, R.string.menu_insert);
		return true;
	}

	@Override
	/*
	 * 在每一次menu生成的时候前都会调用这个方法，在这个方法里边可以动态的修改生成的menu。
	 */
	public boolean onPrepareOptionsMenu(Menu menu) {
		super.onPrepareOptionsMenu(menu);
		final boolean haveItems = getListAdapter().getCount() > 0;
		if (haveItems) {
			// 如果选中一个Item的话
			if (getListView().getSelectedItemId() > 0) {
				menu.removeGroup(1);
				Uri uri = ContentUris.withAppendedId(getIntent().getData(),
						getSelectedItemId());
				Intent intent = new Intent(null, uri);
				menu.add(1, MENU_ITEM_EDIT, 1, "编辑内容").setIntent(intent);
				menu.add(1, MENU_ITEM_DELETE, 1, "删除当前信息");
			}

		}else{
			menu.removeGroup(1);
		}
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		// 插入一条数据
		case MENU_ITEM_INSERT:
			Intent intent0 = new Intent(this, ActivityStudentEditor.class);
			intent0.setAction(ActivityStudentEditor.INSERT_STUDENT_ACTION);
			intent0.setData(getIntent().getData());
			startActivity(intent0);
			return true;
			// 编辑当前数据内容
		case MENU_ITEM_EDIT:
			Intent intent = new Intent(this, ActivityStudentEditor.class);
			intent.setData(item.getIntent().getData());
			intent.setAction(ActivityStudentEditor.EDIT_STUDENT_ACTION);
			startActivity(intent);
			return true;
			// 删除当前数据
		case MENU_ITEM_DELETE:
			Uri uri = ContentUris.withAppendedId(getIntent().getData(),
					getListView().getSelectedItemId());
			getContentResolver().delete(uri, null, null);
			renderListView();

		}
		return super.onOptionsItemSelected(item);
	}

	@Override
	protected void onListItemClick(ListView l, View v, int position, long id) {
		Uri uri = ContentUris.withAppendedId(getIntent().getData(), id);
		
		Log.v("cl","uri: "+uri.getAuthority());
		Log.v("cl","id: "+ id);
		Intent intent = new Intent(this, ActivityStudentEditor.class);
		intent.setData(uri);
		intent.setAction(ActivityStudentEditor.EDIT_STUDENT_ACTION);
		
		startActivity(intent);
/*
		Intent intent = new Intent(this, ActivityStudentEditor.class);
		//intent.setData(item.getIntent().getData());
		intent.setAction(ActivityStudentEditor.EDIT_STUDENT_ACTION);
		startActivity(intent);
		*/
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode,
			Intent intent) {
		super.onActivityResult(requestCode, resultCode, intent);
		//renderListView();
	}

	private void renderListView() {
		Cursor cursor = managedQuery(getIntent().getData(), PROJECTION, null,
				null, "");

		SimpleCursorAdapter adapter = new SimpleCursorAdapter(this,
				R.layout.student_row, cursor, new String[] { "name",
						"age" }, new int[] { R.id.name,
						R.id.age });
		setListAdapter(adapter);
	}
	
	/*
	private void hideTitle()
	{
		requestWindowFeature(Window.FEATURE_NO_TITLE);
	}
	
	private void hideStatusBar()
	{
		int flag=WindowManager.LayoutParams.FLAG_FULLSCREEN;
		Window myWindow = this.getWindow();
		myWindow.setFlags(flag, flag);
	}
	*/
}
