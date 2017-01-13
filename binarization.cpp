// opencv_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp> // �C���N���[�h�t�@�C���w��
#include <opencv2/opencv_lib.hpp> // �ÓI�����N���C�u�����̎w��

using namespace cv; // ���O��Ԃ̎w��

int main()
{
	//lenna.bmp��ǂݍ���
	Mat lenna = imread("lenna-gray.bmp", 0);

	//��l���̍ۂ�臒l��ݒ�
	int pivot = 130;

	//lenna.bmp�Ɠ����傫���̉摜���쐬
	Mat bin_lenna = Mat::zeros(lenna.size().width, lenna.size().height, CV_8UC1);

	//��f�S�ĂɓK�p
	for (int y = 0; y < bin_lenna.rows; ++y) {
		for (int x = 0; x < bin_lenna.cols; ++x) {
			// 臒l���傫���K���l�����ׂ�255(MAX)��
			if (lenna.data[y*lenna.step + x*lenna.elemSize()] > pivot)
				bin_lenna.data[y*lenna.step + x*lenna.elemSize()] = 255;
			// 臒l�ȉ��̊K���l�����ׂ�0(MIN)��
			else
				bin_lenna.data[y*lenna.step + x*lenna.elemSize()] = 0;
				
		}
	}

	//�摜�̕ۑ�
	imwrite("lenna-bin.bmp", bin_lenna);

	//�E�C���h�E�̕\������(0�̓L�[���������܂ŕ��Ȃ�)
	waitKey(0);

	return 0;
}