// opencv_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp> // インクルードファイル指定
#include <opencv2/opencv_lib.hpp> // 静的リンクライブラリの指定

using namespace cv; // 名前空間の指定

int main()
{
	//lenna.bmpを読み込み
	Mat lenna = imread("lenna-color.bmp", 1);

	//lenna.bmpと同じ大きさの画像を作成
	Mat copy_lenna = Mat::zeros(lenna.size().width, lenna.size().height, CV_8UC3);

	//方法その壱（速いけど長い）
	for (int y = 0; y < copy_lenna.rows; ++y) {
		for (int x = 0; x < copy_lenna.cols; ++x) {
			// 画像のチャネル数分だけループ。白黒の場合は1回、カラーの場合は3回　　　　　
			for (int c = 0; c < copy_lenna.channels(); ++c) {
				//チャンネルの画素情報をcopy_lennaへコピー
				copy_lenna.data[y*copy_lenna.step + x*copy_lenna.elemSize() + c] = lenna.data[y*lenna.step + x*lenna.elemSize() + c];
			}
		}
	}

	//方法その弐（遅いけど分かりやすい）
	/*
	for (int y = 0; y < lenna.size().height; y++) {
		for (int x = 0; x < lenna.size().width; x++) {
			//R
			copy_lenna.at<Vec3b>(y, x)[0] = lenna.at<Vec3b>(y, x)[0];
			//G
			copy_lenna.at<Vec3b>(y, x)[1] = lenna.at<Vec3b>(y, x)[1];
			//B
			copy_lenna.at<Vec3b>(y, x)[2] = lenna.at<Vec3b>(y, x)[2];
		}
	}
	*/

	//画像を保存
	imwrite("lenna_copy.bmp", copy_lenna);

	//ウインドウの表示時間(0はキーが押されるまで閉じない)
	waitKey(0);

	return 0;
}

