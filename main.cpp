#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main()
{
	cv::Mat image = cv::imread("image.jpg", 0);	//��� ó��
	cv::namedWindow("Gray-scale Image");
	cv::imshow("Gray-scale Image", image);

	cv::Mat sobelX, sobelY;

	cv::Sobel(image, sobelX, CV_8U, 1, 0, 3, 1.0, 128); // ���� ���� ȣ��(Ŀ�� ������ 3) ���� 0.4
	cv::Sobel(image, sobelY, CV_8U, 0, 1, 3, 1.0, 128); // ���� ���� ȣ��(Ŀ�� ������ 3)
														// 0���� 128�� �׷��̷����� �ش�
														// ���� ���� ��ο� ȭ�ҷ� ǥ��, ��� ���� ���� ���� ǥ��

	cv::namedWindow("Sobel image X");
	cv::imshow("Sobel image X", sobelX);
	cv::namedWindow("Sobel image Y");
	cv::imshow("Sobel image Y", sobelY);


	// �Һ� ������ ����� �Ϲ������� 16��Ʈ ��ȣ �ִ� ��������(CV_16S)���� ���
	// �Һ� ��(norm) ��� (������ ���� �� ����� �Һ� ���� ���� ��� ���� ����)
	cv::Sobel(image, sobelX, CV_16S, 1, 0, 3);
	cv::Sobel(image, sobelY, CV_16S, 0, 1, 3);
	cv::Mat sobel;
	sobel = abs(sobelX) + abs(sobelY); // L1 �� ���

									   // �Һ� ���� 0�� ���� �������, ���� ���� ��ο� ȸ�� �������� �Ҵ��� ������ ��� ����
									   // converTo �޼ҵ��� �ΰ����� �罺���ϸ� �Ķ���͸� ���
	double sobmin, sobmax;
	cv::minMaxLoc(sobel, &sobmin, &sobmax); // �Һ� �ִ� ã��
											// sobelImage = -alpha*sobel + 255 // 8��Ʈ ���� ��ȯ
	cv::Mat sobelImage;
	sobel.convertTo(sobelImage, CV_8U, -255.0 / sobmax, 255);

	cv::namedWindow("Sobel Image Norm");
	cv::imshow("Sobel Image Norm", sobelImage); 

	// ������ ��谪�� ó��
	cv::Mat sobelThresholded;
	cv::threshold(sobelImage, sobelThresholded, 235, 255, cv::THRESH_BINARY);
	// �Һ� �� ���� ��谪 ����(���� ��谪) �Ӱ� 235���� ������ 00(����) : 0~235 ����, 236~255 ���

	cv::namedWindow("Binary Sobel Image LOW");
	cv::imshow("Binary Sobel Image LOW", sobelThresholded);

	cv::threshold(sobelImage, sobelThresholded, 220, 255, cv::THRESH_BINARY);
	// �Һ� �� ���� ��谪 ����(������ ��谪) �Ӱ� 220���� ������ 00(����) : 0~220 ����, 221~255 ���

	cv::namedWindow("Binary Sobel Image MID");
	cv::imshow("Binary Sobel Image MID", sobelThresholded);

	cv::threshold(sobelImage, sobelThresholded, 200, 255, cv::THRESH_BINARY);
	// �Һ� �� ���� ��谪 ����(���� ��谪) �Ӱ� 200���� ������ 00(����) : 0~235 ����, 200~255 ���

	cv::namedWindow("Binary Sobel Image HIGH");
	cv::imshow("Binary Sobel Image HIGH", sobelThresholded);

	cv::waitKey(0);

	return 0;
}

