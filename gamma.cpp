// opencv_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp> // インクルードファイル指定
#include <opencv2/opencv_lib.hpp> // 静的リンクライブラリの指定

using namespace cv; // 名前空間の指定
int trans_table[256];

int main()
{
	//ガンマ補正の係数を設定
	double gamma = 2.0;
	double work = 1.0 / gamma;

	//lenna.bmpを読み込み
	Mat lenna = imread("lenna-gray.bmp", 0);

	//lenna.bmpと同じ大きさの画像を作成
	Mat gam_lenna = Mat::zeros(lenna.size().width, lenna.size().height, CV_8UC1);

	for (int f = 0; f < 256; f++) {
		//コントラスト補正
		trans_table[f] = (int)(255.0*pow((double)f/255.0,work));

		//255.0*(f/255.0)^(1/gamma) > 255
		if (trans_table[f] > 255) trans_table[f] = 255;

		//255.0*(f/255.0)^(1/gamma) < 0
		else if (trans_table[f] < 0) trans_table[f] = 0;
	}

	for (int y = 0; y < gam_lenna.rows; ++y) {
		for (int x = 0; x < gam_lenna.cols; ++x) {
			gam_lenna.data[y*gam_lenna.step + x*gam_lenna.elemSize()] = trans_table[lenna.data[y*lenna.step + x*lenna.elemSize()]];
		}
	}

	//画像を保存
	imwrite("lenna_gam.bmp", gam_lenna);

	//ウインドウの表示時間(0はキーが押されるまで閉じない)
	waitKey(0);

	return 0;
}

