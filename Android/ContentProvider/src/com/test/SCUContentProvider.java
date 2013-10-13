package com.test;

import java.util.Calendar;
import java.util.HashMap;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.Context;
import android.content.UriMatcher;
import android.content.res.Resources;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteQueryBuilder;
import android.net.Uri;
import android.provider.BaseColumns;
import android.text.TextUtils;
import android.util.Log;



public class SCUContentProvider extends ContentProvider {

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
	
	//private static final String STUDENT_NAME;
	//private static final int STUDENT_AGE = 2;

	private static final UriMatcher sUriMatcher;

	private static class DatabaseHelper extends SQLiteOpenHelper {

		DatabaseHelper(Context context) {
			super(context, DATABASE_NAME, null, DATABASE_VERSION);
			Log.i("SCUContentProvider", "DATABASE_VERSION=" + DATABASE_VERSION);
		}

		@Override
		public void onCreate(SQLiteDatabase db) {
			Log.i("SCUContentProvider", "onCreate(SQLiteDatabase db)");
			String sql = "CREATE TABLE " + STUDENT_TABLE_NAME + " ("
					+ BaseColumns._ID + " INTEGER PRIMARY KEY,"
					+ "name" + " TEXT," +"age" 
					+ " TEXT"+");";
			//
			/*
			sql ="CREATE TABLE " + DIARY_TABLE_NAME + " ("
			+ DiaryColumns._ID + " INTEGER PRIMARY KEY,"
			+ DiaryColumns.TITLE + " varchar(255)," + DiaryColumns.BODY
			+ " TEXT," + DiaryColumns.CREATED + " TEXT" + ");";
			*/
			//
			Log.i("SCUContentProvider", "sql="+sql);
			db.execSQL(sql);
		}

		@Override
		public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
			Log.i("SCUContentProvider",
					" onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion)="
							+ newVersion);
			db.execSQL("DROP TABLE IF EXISTS diary");
			onCreate(db);
		}
	}

	private DatabaseHelper mOpenHelper;

	static {
		sUriMatcher = new UriMatcher(UriMatcher.NO_MATCH);
		sUriMatcher.addURI(AUTHORITY, "student", STUDENT);
		sUriMatcher.addURI(AUTHORITY, "student/#", STUDENT_ID);

	}

	@Override
	public boolean onCreate() {
		mOpenHelper = new DatabaseHelper(getContext());
		return true;
	}

	@Override
	public Cursor query(Uri uri, String[] projection, String selection,
			String[] selectionArgs, String sortOrder) {
		SQLiteQueryBuilder qb = new SQLiteQueryBuilder();

		switch (sUriMatcher.match(uri)) {
		case STUDENT:
			qb.setTables(STUDENT_TABLE_NAME);
			break;

		case STUDENT_ID:
			qb.setTables(STUDENT_TABLE_NAME);
			qb.appendWhere(BaseColumns._ID + "="
					+ uri.getPathSegments().get(1));
			break;

		default:
			throw new IllegalArgumentException("Unknown URI " + uri);
		}

		String orderBy;
		if (TextUtils.isEmpty(sortOrder)) {
			orderBy = DEFAULT_SORT_ORDER;
		} else {
			orderBy = sortOrder;
		}

		SQLiteDatabase db = mOpenHelper.getReadableDatabase();
		
		Log.i("cl","Cursor query");
		Cursor c = qb.query(db, projection, selection, selectionArgs, null,
				null, orderBy);
		return c;
	}

	@Override
	public String getType(Uri uri) {
		switch (sUriMatcher.match(uri)) {
		case STUDENT:
			return CONTENT_TYPE;

		case STUDENT_ID:
			return CONTENT_ITEM_TYPE;

		default:
			throw new IllegalArgumentException("Unknown URI " + uri);
		}
	}

	@Override
	public Uri insert(Uri uri, ContentValues initialValues) {
		if (sUriMatcher.match(uri) != STUDENT) {
			throw new IllegalArgumentException("Unknown URI " + uri);
		}

		ContentValues values;
		if (initialValues != null) {
			values = new ContentValues(initialValues);
		} else {
			values = new ContentValues();
		}

		if (values.containsKey("name") == false) {
			values.put("name", getFormateCreatedDate());
		}

		if (values.containsKey("age") == false) {
			Resources r = Resources.getSystem();
			values.put("age", 0);
		}

		

		SQLiteDatabase db = mOpenHelper.getWritableDatabase();
		long rowId = db.insert(STUDENT_TABLE_NAME, "name", values);
		if (rowId > 0) {
			Uri diaryUri = ContentUris.withAppendedId(
					CONTENT_URI, rowId);
			return diaryUri;
		}

		throw new SQLException("Failed to insert row into " + uri);
	}

	@Override
	public int delete(Uri uri, String where, String[] whereArgs) {
		SQLiteDatabase db = mOpenHelper.getWritableDatabase();
		String rowId = uri.getPathSegments().get(1);
		return db
				.delete(STUDENT_TABLE_NAME, BaseColumns._ID + "=" + rowId, null);

	}

	@Override
	public int update(Uri uri, ContentValues values, String where,
			String[] whereArgs) {
		SQLiteDatabase db = mOpenHelper.getWritableDatabase();
		String rowId = uri.getPathSegments().get(1);
		return db.update(STUDENT_TABLE_NAME, values, BaseColumns._ID + "="
				+ rowId, null);

	}

	public static String getFormateCreatedDate() {
		Calendar calendar = Calendar.getInstance();
		String created = calendar.get(Calendar.YEAR) + "年"
				+ calendar.get(Calendar.MONTH) + "月"
				+ calendar.get(Calendar.DAY_OF_MONTH) + "日"
				+ calendar.get(Calendar.HOUR_OF_DAY) + "时"
				+ calendar.get(Calendar.MINUTE) + "分";
		return created;
	}
}
