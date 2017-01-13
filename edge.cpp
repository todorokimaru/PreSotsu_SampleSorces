// opencv_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp> // �C���N���[�h�t�@�C���w��
#include <opencv2/opencv_lib.hpp> // �ÓI�����N���C�u�����̎w��

using namespace cv; // ���O��Ԃ̎w��

//�t�B���^�̐ݒ�
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

	//lenna.bmp��ǂݍ���
	Mat lenna = imread("lenna-gray.bmp", 0);

	//lenna.bmp�Ɠ����傫���̉摜���쐬
	Mat sobel_lenna = Mat::zeros(lenna.size().width, lenna.size().height, CV_8UC1);

	//�␳��̍ŏ�-�ő��ݒ�
	for (int y = 1; y < sobel_lenna.rows - 1; ++y) {
		for (int x = 1; x < sobel_lenna.cols - 1; ++x) {�@�@�@�@
			value = calc(lenna, x, y);
			if (value < min) min = value;
			if (value > max) max = value;
		}
	}

	//�t�B���^����
	for (int y = 1; y < sobel_lenna.rows - 1; ++y) {
		for (int x = 1; x < sobel_lenna.cols - 1; ++x) {�@�@�@�@�@
			value = calc(lenna, x, y);
			// g = (value - min)/(max - min) * 255.0
			sobel_lenna.data[y*sobel_lenna.step + x*sobel_lenna.elemSize()] = (int)((double)(value - min) / (max - min)*255.0);
		}
	}

	//�~�����̏���
	for (int y = 0; y < sobel_lenna.rows; ++y) {
		for (int x = 0; x < sobel_lenna.cols; ++x) {�@�@�@�@
			xsft = 0; ysft = 0;
			if (x == 0) xsft = 1; else if (x == sobel_lenna.cols - 1) xsft = -1;
			if (y == 0) ysft = 1; else if (y == sobel_lenna.rows - 1) ysft = -1;
			if (xsft != 0 || ysft != 0)
				sobel_lenna.data[y*sobel_lenna.step + x*sobel_lenna.elemSize()] = sobel_lenna.data[(y + ysft)*sobel_lenna.step + (x + xsft)*sobel_lenna.elemSize()];
		}
	}

	//�摜��ۑ�
	imwrite("lenna_edge.bmp", sobel_lenna);

	//�E�C���h�E�̕\������(0�̓L�[���������܂ŕ��Ȃ�)
	waitKey(0);

	return 0;
}

