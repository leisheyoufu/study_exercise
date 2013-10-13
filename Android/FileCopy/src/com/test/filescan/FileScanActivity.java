package com.test.filescan;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.media.MediaMetadataRetriever;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

public class FileScanActivity extends Activity {
	/** Called when the activity is first created. */
	private String tag = "FileScanActivity";
	/*
	 * private List<String> picList; private List<String> videoList;
	 */

	private TextView tv;
	private ProgressBar pb;
	private CopyFilesTask copyFilesTask;

	private String fromDir;
	private String toDir;
	private FileUtil fileUtil;
	private long remainCopySize;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		tv = (TextView) findViewById(R.id.textView);
		pb = (ProgressBar) findViewById(R.id.progressBar);
		copyFilesTask = (CopyFilesTask) new CopyFilesTask().execute();

	}

	class CopyFilesTask extends AsyncTask<Integer, Integer, String> {
		// 后面尖括号内分别是参数（例子里是线程休息时间），进度(publishProgress用到)，返回值 类型

		@Override
		protected void onPreExecute() {
			// 第一个执行方法
			fromDir = "/sdcard/movie/";
			toDir = "/sdcard/cl_backup/";
			fileUtil = new FileUtil();
			super.onPreExecute();
		}

		@Override  
	        protected String doInBackground(Integer... params) {  
	            //第二个执行方法,onPreExecute()执行完后执行  

	    	
	    		File f = new File(fromDir);
	    		remainCopySize = fileUtil.getDirSize(f);
	    		fileUtil.setAlreadyCopySize(0);
	    		
	    		 new Thread() {

	    	           @Override

	    	           public void run() {
	    	        		boolean b = fileUtil.copyDirectory(fromDir,
	    		    				toDir);
	    	        
	    	           }

	    	       }.start();
	    		
	    		   Log.i(tag,"remainCopySize " + String.valueOf(remainCopySize));
	        	   Log.i(tag,"current copy size " + String.valueOf(fileUtil.getAlreadyCopySize()));
	        	   while(fileUtil.getAlreadyCopySize()<remainCopySize)
	        	   {
    	        	   Log.i(tag,"remainCopySize " + String.valueOf(remainCopySize));
    	        	   Log.i(tag,"current copy size " + String.valueOf(fileUtil.getAlreadyCopySize()));
    	        		publishProgress((int)(fileUtil.getAlreadyCopySize()*100/remainCopySize));
    	        
	        	   }
	        	   publishProgress(100);
	    		
	    		// boolean b = fileUtil.copyFile("/sdcard/cl_backup1/1/1.bmp",
	    		// "/sdcard/2.bmp");
	    		/*
	    		if (b == true) {
	    			Toast.makeText(this, "文件拷贝成功！！！", 20000).show();
	    		} else {
	    			Toast.makeText(this, "文件拷贝失败！！！", 20000).show();
	    		}
	    		*/
	    
	    		
	    		  
	   
	            return "执行完毕";  
	        }
		@Override
		protected void onProgressUpdate(Integer... progress) {
			// 这个函数在doInBackground调用publishProgress时触发，虽然调用时只有一个参数
			// 但是这里取到的是一个数组,所以要用progesss[0]来取值
			// 第n个参数就用progress[n]来取值
		//	tv.setText(progress[0] + "%");
			if(fileUtil.getfromFilePath() !=null && fileUtil.getToFilePath() !=null)
			{
				tv.setText("从 "+ fileUtil.getfromFilePath()+"    到     "+fileUtil.getToFilePath());
			}
			pb.setProgress(progress[0]);
			super.onProgressUpdate(progress);
		}

		@Override
		protected void onPostExecute(String result) {
			// doInBackground返回时触发，换句话说，就是doInBackground执行完后触发
			// 这里的result就是上面doInBackground执行后的返回值，所以这里是"执行完毕"
			setTitle(result);
			super.onPostExecute(result);
		}

	}

	public void scanPicVideo() {
		/*
		 * FileUtil fileUtil = new FileUtil(); picList = new
		 * ArrayList<String>(); videoList = new ArrayList<String>(); boolean b =
		 * false; //获得外部存储的路径 String mountPath =
		 * fileUtil.getExternalStoragePath();
		 * 
		 * if (mountPath == null) { Log.i(tag, "mountPath is null"); } else {
		 * Log.i(tag, "mountPath is " + String.valueOf(mountPath)); //开始扫描
		 * 图片资源和视频资源 扫描 /mnt/sdcard/external_sd/ b =
		 * fileUtil.scanPicVideoInTF(mountPath, picList, videoList); } //打印扫描结果
		 * 测试用！ if (b) { for (int i = 0; i < picList.size(); i++) { Log.i(tag,
		 * "picList " + picList.get(i)); } for (int i = 0; i < videoList.size();
		 * i++) { Log.i(tag, "videoList " + videoList.get(i)); } }
		 */
	}
}