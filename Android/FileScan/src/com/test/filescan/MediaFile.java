package com.test.filescan;

import android.content.ContentValues;
import android.provider.MediaStore.Audio;
import android.provider.MediaStore.Images;
import android.provider.MediaStore.Video;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

/***
 * MediaScanner helper class.
 * 
 * {@hide}
 */
public class MediaFile {
	// comma separated list of all file extensions supported by the media
	// scanner
	public final static String sFileExtensions;

	// Audio file types
	public static final int FILE_TYPE_MP3 = 1;
	public static final int FILE_TYPE_M4A = 2;
	public static final int FILE_TYPE_WAV = 3;
	public static final int FILE_TYPE_AMR = 4;
	public static final int FILE_TYPE_AWB = 5;
	public static final int FILE_TYPE_WMA = 6;
	public static final int FILE_TYPE_OGG = 7;
	public static final int FILE_TYPE_AAC = 8;
	private static final int FIRST_AUDIO_FILE_TYPE = FILE_TYPE_MP3;
	private static final int LAST_AUDIO_FILE_TYPE = FILE_TYPE_AAC;

	// MIDI file types
	public static final int FILE_TYPE_MID = 11;
	public static final int FILE_TYPE_SMF = 12;
	public static final int FILE_TYPE_IMY = 13;
	private static final int FIRST_MIDI_FILE_TYPE = FILE_TYPE_MID;
	private static final int LAST_MIDI_FILE_TYPE = FILE_TYPE_IMY;

	// Video file types
	public static final int FILE_TYPE_MP4 = 21;
	public static final int FILE_TYPE_TS = 22;
	public static final int FILE_TYPE_3GPP = 23;
	public static final int FILE_TYPE_3GPP2 = 24;
	public static final int FILE_TYPE_WMV = 25;
	public static final int FILE_TYPE_MOV = 26;
	
	public static final int FILE_TYPE_AVI = 27;
	public static final int FILE_TYPE_MPG = 28;
	public static final int FILE_TYPE_MKV = 29;
	private static final int FIRST_VIDEO_FILE_TYPE = FILE_TYPE_MP4;
	private static final int LAST_VIDEO_FILE_TYPE = FILE_TYPE_MKV;

	// Image file types
	public static final int FILE_TYPE_JPEG = 31;
	public static final int FILE_TYPE_GIF = 32;
	public static final int FILE_TYPE_PNG = 33;
	public static final int FILE_TYPE_BMP = 34;
	public static final int FILE_TYPE_WBMP = 35;
	public static final int FILE_TYPE_SVG = 36;
	private static final int FIRST_IMAGE_FILE_TYPE = FILE_TYPE_JPEG;
	private static final int LAST_IMAGE_FILE_TYPE = FILE_TYPE_SVG;

	// Playlist file types
	public static final int FILE_TYPE_M3U = 41;
	public static final int FILE_TYPE_PLS = 42;
	public static final int FILE_TYPE_WPL = 43;
	private static final int FIRST_PLAYLIST_FILE_TYPE = FILE_TYPE_M3U;
	private static final int LAST_PLAYLIST_FILE_TYPE = FILE_TYPE_WPL;

	static class MediaFileType {

		int fileType;
		String mimeType;

		MediaFileType(int fileType, String mimeType) {
			this.fileType = fileType;
			this.mimeType = mimeType;
		}
	}

	private static HashMap<String, MediaFileType> sFileTypeMap = new HashMap<String, MediaFileType>();
	private static HashMap<String, Integer> sMimeTypeMap = new HashMap<String, Integer>();

	static void addFileType(String extension, int fileType, String mimeType) {
		sFileTypeMap.put(extension, new MediaFileType(fileType, mimeType));
		sMimeTypeMap.put(mimeType, Integer.valueOf(fileType));
	}

	static {
		//audio
		addFileType("MP3", FILE_TYPE_MP3, "audio/mpeg");
		addFileType("M4A", FILE_TYPE_M4A, "audio/mp4");
		addFileType("WAV", FILE_TYPE_WAV, "audio/x-wav");
		addFileType("AMR", FILE_TYPE_AMR, "audio/amr");
		addFileType("AWB", FILE_TYPE_AWB, "audio/amr-wb");
		addFileType("WMA", FILE_TYPE_WMA, "audio/x-ms-wma");
		addFileType("OGG", FILE_TYPE_OGG, "application/ogg");
		addFileType("OGA", FILE_TYPE_OGG, "application/ogg");
		addFileType("AAC", FILE_TYPE_AAC, "audio/aac");
		//midi
		addFileType("MID", FILE_TYPE_MID, "audio/midi");
		addFileType("MIDI", FILE_TYPE_MID, "audio/midi");
		addFileType("XMF", FILE_TYPE_MID, "audio/midi");
		addFileType("RTTTL", FILE_TYPE_MID, "audio/midi");
		addFileType("SMF", FILE_TYPE_SMF, "audio/sp-midi");
		addFileType("IMY", FILE_TYPE_IMY, "audio/imelody");
		addFileType("RTX", FILE_TYPE_MID, "audio/midi");
		addFileType("OTA", FILE_TYPE_MID, "audio/midi");
		//media
		addFileType("MPEG", FILE_TYPE_MP4, "video/mpeg");
		addFileType("MP4", FILE_TYPE_MP4, "video/mp4");
		addFileType("MPG", FILE_TYPE_MPG, "video/mpeg");
		addFileType("TS", FILE_TYPE_TS, "video/ts");
		addFileType("3GP", FILE_TYPE_3GPP, "video/3gpp");
		addFileType("3GPP", FILE_TYPE_3GPP, "video/3gpp");
		addFileType("3G2", FILE_TYPE_3GPP2, "video/3gpp2");
		addFileType("3GPP2", FILE_TYPE_3GPP2, "video/3gpp2");
		addFileType("WMV", FILE_TYPE_WMV, "video/x-ms-wmv");
		addFileType("MOV", FILE_TYPE_MOV, "video/x-ms-wmv");
		addFileType("MKV", FILE_TYPE_MKV, "video/x-ms-asf");
		addFileType("AVI", FILE_TYPE_AVI, "video/x-ms-asf");
	
		//picture
		addFileType("JPG", FILE_TYPE_JPEG, "image/jpeg");
		addFileType("JPEG", FILE_TYPE_JPEG, "image/jpeg");
		addFileType("GIF", FILE_TYPE_GIF, "image/gif");
		addFileType("PNG", FILE_TYPE_PNG, "image/png");
		addFileType("BMP", FILE_TYPE_BMP, "image/x-ms-bmp");
		addFileType("WBMP", FILE_TYPE_WBMP, "image/vnd.wap.wbmp");
		addFileType("SVG", FILE_TYPE_SVG, "image/svg");
		//playlst
		addFileType("M3U", FILE_TYPE_M3U, "audio/x-mpegurl");
		addFileType("PLS", FILE_TYPE_PLS, "audio/x-scpls");
		addFileType("WPL", FILE_TYPE_WPL, "application/vnd.ms-wpl");

		// compute file extensions list for native Media Scanner
		StringBuilder builder = new StringBuilder();
		Iterator<String> iterator = sFileTypeMap.keySet().iterator();

		while (iterator.hasNext()) {
			if (builder.length() > 0) {
				builder.append(',');
			}
			builder.append(iterator.next());
		}
		sFileExtensions = builder.toString();
	}

	public static boolean isAudioFileType(int fileType) {
		return ((fileType >= FIRST_AUDIO_FILE_TYPE && fileType <= LAST_AUDIO_FILE_TYPE) || (fileType >= FIRST_MIDI_FILE_TYPE && fileType <= LAST_MIDI_FILE_TYPE));
	}

	/* *********************************************************
	 * 根据MediaType中的fileType判断是否为视频文件
	 * Para fileType 
	 * return 是视频文件返回true 否则 false
	 ***********************************************************/
	public static boolean isVideoFileType(int fileType) {
		return (fileType >= FIRST_VIDEO_FILE_TYPE && fileType <= LAST_VIDEO_FILE_TYPE);
	}

	/* *********************************************************
	 * 根据MediaType中的fileType判断是否为图片文件
	 * Para fileType 
	 * return 是图片文件返回true 否则 false
	 ***********************************************************/
	public static boolean isImageFileType(int fileType) {
		return (fileType >= FIRST_IMAGE_FILE_TYPE && fileType <= LAST_IMAGE_FILE_TYPE);
	}

	
	public static boolean isPlayListFileType(int fileType) {
		return (fileType >= FIRST_PLAYLIST_FILE_TYPE && fileType <= LAST_PLAYLIST_FILE_TYPE);
	}
	/* *********************************************************
	 * 根据文件名判断媒体文件类型
	 * Para path:String 传入的文件路径
	 * return 如果是能够识别的文件类型返回MediaType,否则返回空
	 * *********************************************************/
	public static MediaFileType getFileType(String path) {
		int lastDot = path.lastIndexOf(".");
		if (lastDot < 0)
			return null;
		return sFileTypeMap.get(path.substring(lastDot + 1).toUpperCase());
	}

	public static int getFileTypeForMimeType(String mimeType) {
		Integer value = sMimeTypeMap.get(mimeType);
		return (value == null ? 0 : value.intValue());
	}

}
