// opencv_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp> // インクルードファイル指定
#include <opencv2/opencv_lib.hpp> // 静的リンクライブラリの指定

using namespace cv; // 名前空間の指定

//フィルタの設定
int Cij[3][3] =
{ {-1, 0, 1},
  {-2, 0, 2},
  {-1, 0, 1} };

double K = 1.0;

int calc(Mat, int, int);

int calc(Mat img, int x, int y) {
	int value = 0;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			value += Cij[j][i] * img.data[(y + i - 1)*img.step + (x + j - 1)*img.elemSize()];
		}
	}
	return (int)(K*value);
}

int main()
{
	int xsft, ysft, value, min = 255, max = 0;

	//lenna.bmpを読み込み
	Mat lenna = imread("lenna-gray.bmp", 0);

	//lenna.bmpと同じ大きさの画像を作成
	Mat sobel_lenna = Mat::zeros(lenna.size().width, lenna.size().height, CV_8UC1);

	//補正後の最小-最大を設定
	for (int y = 1; y < sobel_lenna.rows - 1; ++y) {
		for (int x = 1; x < sobel_lenna.cols - 1; ++x) {　　　　
			value = calc(lenna, x, y);
			if (value < min) min = value;
			if (value > max) max = value;
		}
	}

	//フィルタ処理
	for (int y = 1; y < sobel_lenna.rows - 1; ++y) {
		for (int x = 1; x < sobel_lenna.cols - 1; ++x) {　　　　　
			value = calc(lenna, x, y);
			// g = (value - min)/(max - min) * 255.0
			sobel_lenna.data[y*sobel_lenna.step + x*sobel_lenna.elemSize()] = (int)((double)(value - min) / (max - min)*255.0);
		}
	}

	//円周部の処理
	for (int y = 0; y < sobel_lenna.rows; ++y) {
		for (int x = 0; x < sobel_lenna.cols; ++x) {　　　　
			xsft = 0; ysft = 0;
			if (x == 0) xsft = 1; else if (x == sobel_lenna.cols - 1) xsft = -1;
			if (y == 0) ysft = 1; else if (y == sobel_lenna.rows - 1) ysft = -1;
			if (xsft != 0 || ysft != 0)
				sobel_lenna.data[y*sobel_lenna.step + x*sobel_lenna.elemSize()] = sobel_lenna.data[(y + ysft)*sobel_lenna.step + (x + xsft)*sobel_lenna.elemSize()];
		}
	}

	//画像を保存
	imwrite("lenna_edge.bmp", sobel_lenna);

	//ウインドウの表示時間(0はキーが押されるまで閉じない)
	waitKey(0);

	return 0;
}

