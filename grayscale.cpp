// opencv_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp> // インクルードファイル指定
#include <opencv2/opencv_lib.hpp> // 静的リンクライブラリの指定

using namespace cv; // 名前空間の指定

int main()
{
	//lenna.bmpを読み込み
	Mat lenna = imread("lenna-color.bmp",1);

	//グレースケール用の画像作成
	Mat gray_lenna = Mat::zeros(lenna.size().width, lenna.size().height, CV_8UC1);
	int Y;
	int channel[3];

	//画素全てに適用させる
	for (int y = 0; y < lenna.rows; ++y) {
		for (int x = 0; x < lenna.cols; ++x) {
			// 画像のチャネル数分だけループ。白黒の場合は1回、カラーの場合は3回　　　　　
			for (int c = 0; c < lenna.channels(); ++c) {
				channel[c] = lenna.data[y*lenna.step + x*lenna.elemSize() + c];
			}
			//NTSC係数の加重平均法を用いる
			Y = (int)(0.298912*channel[0] + 0.586611*channel[1] + 0.114478*channel[2]);
			gray_lenna.data[y*gray_lenna.step + x*gray_lenna.elemSize()] = Y;
		}
	}

	//画像の保存
	imwrite("lenna-gray.bmp", gray_lenna);

	//ウインドウの表示時間(0はキーが押されるまで閉じない)
	waitKey(0);

	return 0;
}

