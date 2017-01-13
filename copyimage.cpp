// opencv_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp> // �C���N���[�h�t�@�C���w��
#include <opencv2/opencv_lib.hpp> // �ÓI�����N���C�u�����̎w��

using namespace cv; // ���O��Ԃ̎w��

int main()
{
	//lenna.bmp��ǂݍ���
	Mat lenna = imread("lenna-color.bmp", 1);

	//lenna.bmp�Ɠ����傫���̉摜���쐬
	Mat copy_lenna = Mat::zeros(lenna.size().width, lenna.size().height, CV_8UC3);

	//���@���̈�i�������ǒ����j
	for (int y = 0; y < copy_lenna.rows; ++y) {
		for (int x = 0; x < copy_lenna.cols; ++x) {
			// �摜�̃`���l�������������[�v�B�����̏ꍇ��1��A�J���[�̏ꍇ��3��@�@�@�@�@
			for (int c = 0; c < copy_lenna.channels(); ++c) {
				//�`�����l���̉�f����copy_lenna�փR�s�[
				copy_lenna.data[y*copy_lenna.step + x*copy_lenna.elemSize() + c] = lenna.data[y*lenna.step + x*lenna.elemSize() + c];
			}
		}
	}

	//���@���̓�i�x�����Ǖ�����₷���j
	/*
	for (int y = 0; y < lenna.size().height; y++) {
		for (int x = 0; x < lenna.size().width; x++) {
			//R
			copy_lenna.at<Vec3b>(y, x)[0] = lenna.at<Vec3b>(y, x)[0];
			//G
			copy_lenna.at<Vec3b>(y, x)[1] = lenna.at<Vec3b>(y, x)[1];
			//B
			copy_lenna.at<Vec3b>(y, x)[2] = lenna.at<Vec3b>(y, x)[2];
		}
	}
	*/

	//�摜��ۑ�
	imwrite("lenna_copy.bmp", copy_lenna);

	//�E�C���h�E�̕\������(0�̓L�[���������܂ŕ��Ȃ�)
	waitKey(0);

	return 0;
}

