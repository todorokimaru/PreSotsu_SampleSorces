// opencv_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp> // �C���N���[�h�t�@�C���w��
#include <opencv2/opencv_lib.hpp> // �ÓI�����N���C�u�����̎w��

using namespace cv; // ���O��Ԃ̎w��
int trans_table[256];

int main()
{
	//�K���}�␳�̌W����ݒ�
	double gamma = 2.0;
	double work = 1.0 / gamma;

	//lenna.bmp��ǂݍ���
	Mat lenna = imread("lenna-gray.bmp", 0);

	//lenna.bmp�Ɠ����傫���̉摜���쐬
	Mat gam_lenna = Mat::zeros(lenna.size().width, lenna.size().height, CV_8UC1);

	for (int f = 0; f < 256; f++) {
		//�R���g���X�g�␳
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

	//�摜��ۑ�
	imwrite("lenna_gam.bmp", gam_lenna);

	//�E�C���h�E�̕\������(0�̓L�[���������܂ŕ��Ȃ�)
	waitKey(0);

	return 0;
}

