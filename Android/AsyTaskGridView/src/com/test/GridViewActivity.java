package com.test;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.R.color;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Rect;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.view.View.OnFocusChangeListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

public class GridViewActivity extends Activity {
	private GridView gridview;
	private Context context;
	private List lstImageItem;
	private GridViewAdapter gridViewAdapter;
	private ImageUpdateTask imageUpdateTask;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		context = this;
		gridview = (GridView) findViewById(R.id.GridView);
		gridview.setNumColumns(3);

		imageUpdateTask = (ImageUpdateTask) new ImageUpdateTask().execute();

	}

	class ImageUpdateTask extends
			AsyncTask<Void, HashMap<String, Object>, String> {
		@Override
		protected void onPreExecute() {

			lstImageItem = new ArrayList<HashMap<String, Object>>();
			gridViewAdapter = new GridViewAdapter(context, lstImageItem);
			gridview.setAdapter(gridViewAdapter);
			// 第一个执行方法
			super.onPreExecute();

		}

		@Override
		protected String doInBackground(Void... params) {
			for (int i = 0; i < 8; i++) {
				HashMap<String, Object> map = new HashMap<String, Object>();
				map.put("ItemImage", R.drawable.gallery_photo_1 + i);// 添加图像资源的ID
				map.put("ItemText", "NO." + String.valueOf(i));// 按序号做ItemText
				publishProgress(map);
			}

			return "执行完毕";
		}

		@Override
		public void onProgressUpdate(HashMap<String, Object>... maps) {
			for (HashMap<String, Object> map : maps) {
				lstImageItem.add(map);
			}
			// 这个是通知adapter有新的photo update.
			gridViewAdapter.notifyDataSetChanged();
		}

		@Override
		protected void onPostExecute(String result) {
			// doInBackground返回时触发，换句话说，就是doInBackground执行完后触发
			Log.i("cl","postExecute");
			super.onPostExecute(result);

		}

	}
}