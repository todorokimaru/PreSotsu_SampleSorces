// opencv_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp> // �C���N���[�h�t�@�C���w��
#include <opencv2/opencv_lib.hpp> // �ÓI�����N���C�u�����̎w��

using namespace cv; // ���O��Ԃ̎w��

int main()
{
	//lenna.bmp��ǂݍ���
	Mat lenna = imread("lenna-color.bmp",1);

	//�O���[�X�P�[���p�̉摜�쐬
	Mat gray_lenna = Mat::zeros(lenna.size().width, lenna.size().height, CV_8UC1);
	int Y;
	int channel[3];

	//��f�S�ĂɓK�p������
	for (int y = 0; y < lenna.rows; ++y) {
		for (int x = 0; x < lenna.cols; ++x) {
			// �摜�̃`���l�������������[�v�B�����̏ꍇ��1��A�J���[�̏ꍇ��3��@�@�@�@�@
			for (int c = 0; c < lenna.channels(); ++c) {
				channel[c] = lenna.data[y*lenna.step + x*lenna.elemSize() + c];
			}
			//NTSC�W���̉��d���ϖ@��p����
			Y = (int)(0.298912*channel[0] + 0.586611*channel[1] + 0.114478*channel[2]);
			gray_lenna.data[y*gray_lenna.step + x*gray_lenna.elemSize()] = Y;
		}
	}

	//�摜�̕ۑ�
	imwrite("lenna-gray.bmp", gray_lenna);

	//�E�C���h�E�̕\������(0�̓L�[���������܂ŕ��Ȃ�)
	waitKey(0);

	return 0;
}

