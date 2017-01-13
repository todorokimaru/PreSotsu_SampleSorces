// opencv_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp> // �C���N���[�h�t�@�C���w��
#include <opencv2/opencv_lib.hpp> // �ÓI�����N���C�u�����̎w��

using namespace cv; // ���O��Ԃ̎w��
int trans_table[256];

int main()
{
	//�R���g���X�g�␳�̌W����ݒ�
	double K = 4.0;

	//lenna.bmp��ǂݍ���
	Mat lenna = imread("lenna-gray.bmp", 0);

	//lenna.bmp�Ɠ����傫���̉摜���쐬
	Mat cont_lenna = Mat::zeros(lenna.size().width, lenna.size().height, CV_8UC1);

	for (int f = 0; f < 256; f++) {
		//�R���g���X�g�␳
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

	//�摜��ۑ�
	imwrite("lenna_cont.bmp", cont_lenna);

	//�E�C���h�E�̕\������(0�̓L�[���������܂ŕ��Ȃ�)
	waitKey(0);

	return 0;
}

