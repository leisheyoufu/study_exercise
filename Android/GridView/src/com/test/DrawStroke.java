package com.test;

import android.graphics.Bitmap;
import android.graphics.Color;
import android.util.Log;

public class DrawStroke {
	
	static void drawTop(Bitmap bmp,int color)
	{
		for(int i=0;i<bmp.getWidth();i++)
		{
			bmp.setPixel(i, 0,color);
		}
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
	
	static void DrawRect(Bitmap bmp,int color)
	{
		drawTop(bmp,color);
		drawLeft(bmp,color);
		drawRight(bmp,color);
		drawBottom(bmp,color);		
	}
	

}
