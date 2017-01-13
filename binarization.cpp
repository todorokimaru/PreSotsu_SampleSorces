// opencv_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp> // インクルードファイル指定
#include <opencv2/opencv_lib.hpp> // 静的リンクライブラリの指定

using namespace cv; // 名前空間の指定

int main()
{
	//lenna.bmpを読み込み
	Mat lenna = imread("lenna-gray.bmp", 0);

	//二値化の際の閾値を設定
	int pivot = 130;

	//lenna.bmpと同じ大きさの画像を作成
	Mat bin_lenna = Mat::zeros(lenna.size().width, lenna.size().height, CV_8UC1);

	//画素全てに適用
	for (int y = 0; y < bin_lenna.rows; ++y) {
		for (int x = 0; x < bin_lenna.cols; ++x) {
			// 閾値より大きい階調値をすべて255(MAX)に
			if (lenna.data[y*lenna.step + x*lenna.elemSize()] > pivot)
				bin_lenna.data[y*lenna.step + x*lenna.elemSize()] = 255;
			// 閾値以下の階調値をすべて0(MIN)に
			else
				bin_lenna.data[y*lenna.step + x*lenna.elemSize()] = 0;
				
		}
	}

	//画像の保存
	imwrite("lenna-bin.bmp", bin_lenna);

	//ウインドウの表示時間(0はキーが押されるまで閉じない)
	waitKey(0);

	return 0;
}