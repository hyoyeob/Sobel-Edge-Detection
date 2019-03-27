#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main()
{
	cv::Mat image = cv::imread("image.jpg", 0);	//흑백 처리
	cv::namedWindow("Gray-scale Image");
	cv::imshow("Gray-scale Image", image);

	cv::Mat sobelX, sobelY;

	cv::Sobel(image, sobelX, CV_8U, 1, 0, 3, 1.0, 128); // 수평 필터 호출(커널 사이즈 3) 각도 0.4
	cv::Sobel(image, sobelY, CV_8U, 0, 1, 3, 1.0, 128); // 수직 필터 호출(커널 사이즈 3)
														// 0값은 128인 그레이레벨에 해당
														// 음수 값은 어두운 화소로 표현, 양수 값은 밝은 값을 표현

	cv::namedWindow("Sobel image X");
	cv::imshow("Sobel image X", sobelX);
	cv::namedWindow("Sobel image Y");
	cv::imshow("Sobel image Y", sobelY);


	// 소벨 필터의 결과는 일반적으로 16비트 부호 있는 정수영상(CV_16S)에서 계산
	// 소벨 놈(norm) 계산 (수직과 수평 두 결과의 소벨 필터 놈을 얻기 위해 조합)
	cv::Sobel(image, sobelX, CV_16S, 1, 0, 3);
	cv::Sobel(image, sobelY, CV_16S, 0, 1, 3);
	cv::Mat sobel;
	sobel = abs(sobelX) + abs(sobelY); // L1 놈 계산

									   // 소벨 놈은 0인 값을 흰색으로, 높은 값을 어두운 회색 음영으로 할당한 영상을 얻기 위해
									   // converTo 메소드의 부가적인 재스케일링 파라미터를 사용
	double sobmin, sobmax;
	cv::minMaxLoc(sobel, &sobmin, &sobmax); // 소벨 최댓값 찾기
											// sobelImage = -alpha*sobel + 255 // 8비트 영상 변환
	cv::Mat sobelImage;
	sobel.convertTo(sobelImage, CV_8U, -255.0 / sobmax, 255);

	cv::namedWindow("Sobel Image Norm");
	cv::imshow("Sobel Image Norm", sobelImage); 

	// 영상의 경계값을 처리
	cv::Mat sobelThresholded;
	cv::threshold(sobelImage, sobelThresholded, 235, 255, cv::THRESH_BINARY);
	// 소벨 놈에 대한 경계값 적용(낮은 경계값) 임계 235보다 낮으면 00(검정) : 0~235 검정, 236~255 흰색

	cv::namedWindow("Binary Sobel Image LOW");
	cv::imshow("Binary Sobel Image LOW", sobelThresholded);

	cv::threshold(sobelImage, sobelThresholded, 220, 255, cv::THRESH_BINARY);
	// 소벨 놈에 대한 경계값 적용(적당한 경계값) 임계 220보다 낮으면 00(검정) : 0~220 검정, 221~255 흰색

	cv::namedWindow("Binary Sobel Image MID");
	cv::imshow("Binary Sobel Image MID", sobelThresholded);

	cv::threshold(sobelImage, sobelThresholded, 200, 255, cv::THRESH_BINARY);
	// 소벨 놈에 대한 경계값 적용(높은 경계값) 임계 200보다 낮으면 00(검정) : 0~235 검정, 200~255 흰색

	cv::namedWindow("Binary Sobel Image HIGH");
	cv::imshow("Binary Sobel Image HIGH", sobelThresholded);

	cv::waitKey(0);

	return 0;
}

