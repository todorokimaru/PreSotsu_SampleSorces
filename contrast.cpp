// opencv_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp> // インクルードファイル指定
#include <opencv2/opencv_lib.hpp> // 静的リンクライブラリの指定

using namespace cv; // 名前空間の指定
int trans_table[256];

int main()
{
	//コントラスト補正の係数を設定
	double K = 4.0;

	//lenna.bmpを読み込み
	Mat lenna = imread("lenna-gray.bmp", 0);

	//lenna.bmpと同じ大きさの画像を作成
	Mat cont_lenna = Mat::zeros(lenna.size().width, lenna.size().height, CV_8UC1);

	for (int f = 0; f < 256; f++) {
		//コントラスト補正
		trans_table[f] = (int)(K*(f - 128)) + 128;

		//K*(f-128)+128 > 255
		if (trans_table[f] > 255) trans_table[f] = 255;

		//K*(f-128)+128 < 0
		else if (trans_table[f] < 0) trans_table[f] = 0;
	}

	for (int y = 0; y < cont_lenna.rows; ++y) {
		for (int x = 0; x < cont_lenna.cols; ++x) {
			cont_lenna.data[y*cont_lenna.step + x*cont_lenna.elemSize()] = trans_table[lenna.data[y*lenna.step + x*lenna.elemSize()]];
		}
	}

	//画像を保存
	imwrite("lenna_cont.bmp", cont_lenna);

	//ウインドウの表示時間(0はキーが押されるまで閉じない)
	waitKey(0);

	return 0;
}

