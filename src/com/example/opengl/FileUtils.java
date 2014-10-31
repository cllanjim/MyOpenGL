package com.example.opengl;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.content.res.AssetManager;
import android.util.Log;

public class FileUtils {

	static AssetManager _Assets;
	static String destDirStr ="/Android/data/com.example.opengl";
	static  Boolean IsFiles()
	{
		
			// 获取扩展SD卡设备状态
			String sDStateString = android.os.Environment.getExternalStorageState();
			File myFile = null;
			// 拥有可读可写权限
			if (sDStateString.equals(android.os.Environment.MEDIA_MOUNTED))
			{

							try {

					// 获取扩展存储设备的文件目录
					File SDFile = android.os.Environment
							.getExternalStorageDirectory();
					File destDir = new File(SDFile.getAbsolutePath() + destDirStr);// 文件目录

					if (!destDir.exists()) {// 判断目录是否存在，不存在创建
						destDir.mkdir();// 创建目录
						return true;
					}
				}
				finally
				{
				
				}
			}
			return false;	
	}
	static void CopyAssets(String assetDir, String dir) {
		String[] files;
		try {
			files = _Assets.list(assetDir);
		} catch (IOException e1) {
			return;
		}
		// 获取扩展存储设备的文件目录
		File mWorkingPath = new File(dir);
		// if this directory does not exists, make one.
		if (!mWorkingPath.exists()) {
			if (!mWorkingPath.mkdirs()) {
				Log.e("--CopyAssets--", "cannot create directory.");
			}
		}
		for (int i = 0; i < files.length; i++) {
			try {
				String fileName = files[i];
				// we make sure file name not contains '.' to be a folder.
				if (!fileName.contains(".")) {
					if (0 == assetDir.length()) {
						CopyAssets(fileName, dir + fileName + "/");
					} else {
						CopyAssets(assetDir + "/" + fileName, dir + fileName
								+ "/");
					}
					continue;
				}
				File outFile = new File(mWorkingPath, fileName);
				if (outFile.exists())
					outFile.delete();
				InputStream in = null;
				if (0 != assetDir.length())
					in = _Assets.open(assetDir + "/" + fileName);
				else
					in = _Assets.open(fileName);
				OutputStream out = new FileOutputStream(outFile);
				// Transfer bytes from in to out
				byte[] buf = new byte[1024];
				int len;
				while ((len = in.read(buf)) > 0) {
					out.write(buf, 0, len);
				}
				in.close();
				out.close();
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
