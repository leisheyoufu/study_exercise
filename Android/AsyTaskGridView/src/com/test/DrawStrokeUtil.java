package com.test;

import android.graphics.Bitmap;
import android.graphics.Color;
import android.util.Log;

public class DrawStrokeUtil {
	
	static Bitmap drawTop(Bitmap bmp,int color)
	{
		for(int i=0;i<bmp.getWidth();i++)
		{
			bmp.setPixel(i, 0,color);
		}
		return bmp;
	}
	
	static void drawLeft(Bitmap bmp,int color)
	{
		for(int i=0;i<bmp.getHeight();i++)
		{
			bmp.setPixel(0, i,color);
		}
	}
	
	static void drawRight(Bitmap bmp,int color)
	{
		for(int i=0;i<bmp.getHeight();i++)
		{
			bmp.setPixel(bmp.getWidth()-1, i,color);
		}
	}
	
	static void drawBottom(Bitmap bmp,int color)
	{
		for(int i=0;i<bmp.getWidth();i++)
		{
			bmp.setPixel(i,bmp.getHeight()-1,color);
		}
	}
	
	static void drawRect(Bitmap bmp,int color)
	{
		drawTop(bmp,color);
		drawLeft(bmp,color);
		drawRight(bmp,color);
		drawBottom(bmp,color);		
	}
	
	public static Bitmap copyPixel(Bitmap bmp)
	{
		 Bitmap overlay = Bitmap.createBitmap(bmp.getWidth(), bmp.getHeight(), Bitmap.Config.RGB_565);  
			for(int i=0;i<bmp.getWidth();i++)
			{
				for(int j=0;j<bmp.getHeight();j++)
				{
					int oldColor = bmp.getPixel(i, j);
					overlay.setPixel(i, j, oldColor);
				}
			}
			return overlay;
	}
}
