
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include <opencv2/opencv.hpp>

#include "shared.h"

using std::string;

static const int n_frames = 85;

static const string frames_dir = R"(E:\video\frames\)";
static const string output_dir = outputDirectory();

//static const string left_page_file_name = leftPageFileName();
//static const string right_page_file_name = rightPageFileName();

void transform(cv::Mat &bg, const std::string &file_name, float pos[][2]) {

	auto img = cv::imread(file_name);

	auto w = img.cols;
	auto h = img.rows;

	using cv::Point2f;

	Point2f srcTri[4] = {
		Point2f(0, 0),
		Point2f(w, 0),
		Point2f(0, h),
		Point2f(w, h)
	};

	Point2f dstTri[4] = {
		Point2f(pos[0][0], pos[0][1]),
		Point2f(pos[1][0], pos[1][1]),
		Point2f(pos[2][0], pos[2][1]),
		Point2f(pos[3][0], pos[3][1]),
	};

	auto warp_mat = cv::getPerspectiveTransform(srcTri, dstTri);
	
	cv::warpPerspective(img, bg, warp_mat, bg.size(), cv::INTER_LINEAR, cv::BORDER_TRANSPARENT);
}

void applyMask(cv::Mat &dst, cv::Mat &src, cv::Mat &mask) {

	auto w = mask.cols;
	auto h = mask.rows;

	if (!h && !w) { return; }

	assert(w == src.cols && h == src.rows);
	assert(w == dst.cols && h == dst.rows);

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			auto m = mask.at<cv::Vec3b>(y, x);
			if (m[0] == 255) {
				dst.at<cv::Vec3b>(y, x) = src.at<cv::Vec3b>(y, x);
			}
		}
	}

}

int trump_gif_main(int argc, char *argv[]) {

	auto left_page = cv::imread(leftPageFileName());
	auto right_page = cv::imread(rightPageFileName());

	//
	std::ostringstream rect_file_name;
	rect_file_name << frames_dir << "0_rect.txt";
	std::ifstream rect_fin(rect_file_name.str());

	cv::VideoWriter outputVideo;
	
	for (int i = 1; i <= n_frames; ++i) {

		//
		std::ostringstream ifname;
		ifname << frames_dir << "Layer " << i << ".png";
		cv::Mat img = cv::imread(ifname.str());

		std::ostringstream mask_name;
		mask_name << frames_dir << "Layer " << i << " mask.png";
		cv::Mat mask = cv::imread(mask_name.str());

		if (i == 1) {
			if (!outputVideo.open(R"(e:\video\output.avi)",
				CV_FOURCC('D', 'I', 'V', 'X'),
				10, cv::Size(img.cols, img.rows))) {
				return -1;
			}
		}

		//
		std::cout << ifname.str() << std::endl;

		int fid;
		rect_fin >> fid;

		float pos[8][2];
		for (int ip = 0; ip < 8; ++ip) {
			rect_fin >> pos[ip][0] >> pos[ip][1];
			//printf("%f %f\n", pos[ip][0], pos[ip][1]);
		}

		//
		cv::Mat new_img;
		img.copyTo(new_img);

		//
		transform(new_img, leftPageFileName(), pos);
		transform(new_img, rightPageFileName(), pos + 4);

		applyMask(new_img, img, mask);

		//
		std::ostringstream ofname;
		ofname << output_dir << "Layer " << i << ".png";
		cv::imwrite(ofname.str(), new_img);

		outputVideo << new_img;
	}

	outputVideo.release();

	return 0;
}

#include <QtWidgets/QApplication>
#include "trumpgifmainwindow.h"

int main(int argc, char *argv[]) {

	// trump-gif left-page right-page output-dir
	if (argc == 3 || argc == 4 ) {
		printf("pages: %s %s\n", argv[1], argv[2]);
		setLeftPageFileName(argv[1]);
		setRightPageFileName(argv[2]);
		if (argc == 4) {
			printf("output dir: %s\n", argv[3]);
		}
		trump_gif_main(argc, argv);
		return 0;
	} else	if (argc != 1) {
		printf("invalid argument\n");
		printf("trump-gif left-page right-page [output-dir]\n");
		return -1;
	}

	QApplication app(argc, argv);

	TrumpGIFMainWindow main_window;
	main_window.show();

	auto ret =  app.exec();

	trump_gif_main(argc, argv);

	return ret;
}
