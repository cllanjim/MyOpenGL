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
		
			// ��ȡ��չSD���豸״̬
			String sDStateString = android.os.Environment.getExternalStorageState();
			File myFile = null;
			// ӵ�пɶ���дȨ��
			if (sDStateString.equals(android.os.Environment.MEDIA_MOUNTED))
			{

							try {

					// ��ȡ��չ�洢�豸���ļ�Ŀ¼
					File SDFile = android.os.Environment
							.getExternalStorageDirectory();
					File destDir = new File(SDFile.getAbsolutePath() + destDirStr);// �ļ�Ŀ¼

					if (!destDir.exists()) {// �ж�Ŀ¼�Ƿ���ڣ������ڴ���
						destDir.mkdir();// ����Ŀ¼
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
		// ��ȡ��չ�洢�豸���ļ�Ŀ¼
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
