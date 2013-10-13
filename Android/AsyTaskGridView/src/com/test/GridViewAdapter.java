package com.test;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.drawable.AnimationDrawable;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnFocusChangeListener;
import android.view.View.OnHoverListener;
import android.view.ViewGroup;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

class GridViewAdapter extends BaseAdapter {

	private MyView tag;
	private Context context;
	private List<HashMap<String, String>> list;

	public GridViewAdapter(Context context, List<HashMap<String, String>> list) {
		this.list = list;
		this.context = context;
	}
	
	@Override  
    public void notifyDataSetChanged() {  
        super.notifyDataSetChanged();  
    }  

	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		return list.size();
	}

	/* 得到Item */
	@Override
	public Object getItem(int position) {
		// TODO Auto-generated method stub
		return position;
	}

	/* 获取Items的ID */
	@Override
	public long getItemId(int position) {
		// TODO Auto-generated method stub
		return position;
	}

	/* 获取要显示的View对象 */
	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		if (convertView == null) {
			View v = LayoutInflater.from(context).inflate(R.layout.grid, null);
			tag = new MyView();
			tag.imageView = (ImageView) v.findViewById(R.id.ItemImage);
			tag.textView = (TextView) v.findViewById(R.id.ItemText);

			v.setTag(tag);
			convertView = v;
		} else {
			tag = (MyView) convertView.getTag();
		}
		tag.imageView.setImageResource(R.drawable.gallery_photo_1 + position);
		tag.textView.setText("NO" + String.valueOf(position));
		OnItemClickListener clickListener = new OnItemClickListener(
				tag.imageView, tag.textView, position);
		convertView.setOnClickListener(clickListener);

		return convertView;
	}

	class OnItemClickListener implements OnClickListener {
		private ImageView imageView;
		private TextView textView;
		private int position;
		private Handler handler;
		private Runnable runnable;

		OnItemClickListener(ImageView imageView, TextView textView, int position) {
			this.imageView = imageView;
			this.position = position;
			this.textView = textView;

			handler = new Handler();
		}

		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub

			runnable = new Runnable() {
				public void run() {

					Bitmap bitmap = BitmapFactory.decodeResource(
							context.getResources(), R.drawable.gallery_photo_1
									+ position);
					imageView.setImageBitmap(bitmap);
				}
			};
			handler.postDelayed(runnable, 500);
			Bitmap bitmap = BitmapFactory.decodeResource(
					context.getResources(), R.drawable.gallery_photo_1
							+ position);
			Bitmap copyBitMap = DrawStrokeUtil.copyPixel(bitmap);
			
			DrawStrokeUtil.drawRect(copyBitMap, Color.YELLOW);
			imageView.setImageBitmap(copyBitMap);

			Animation alphaAnimation = new AlphaAnimation(1.0f, 0.3f);
			alphaAnimation.setDuration(500);
			imageView.startAnimation(alphaAnimation);
			textView.startAnimation(alphaAnimation);
		}
	}
}

class MyView {
	ImageView imageView;
	TextView textView;
}