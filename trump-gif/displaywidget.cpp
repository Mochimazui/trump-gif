#include "displaywidget.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include <QEvent>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>

#include "shared.h"

using std::string;

static const int n_frames = 85;

static const string frames_dir = R"(E:\video\frames\)";
//static const string output_dir = outputDirectory();
//
//static const string left_page_file_name = leftPageFileName();
//static const string right_page_file_name = rightPageFileName();

DisplayWidget::DisplayWidget(QWidget *parent)
	: QWidget(parent)
{
	loadPageRects();

	_left_page = cv::imread(leftPageFileName());
	_right_page = cv::imread(rightPageFileName());

	loadFrame(0);
}

DisplayWidget::~DisplayWidget()
{
}

void DisplayWidget::priviousFrame() {
	if (_current_frame != 0) { 
		--_current_frame; 
		loadFrame(_current_frame);
		emit updateFrameID(_current_frame);
	}
	update();
}

void DisplayWidget::nextFrame() {
	if (_current_frame != 84) {
		++_current_frame;
		loadFrame(_current_frame);
		emit updateFrameID(_current_frame);
	}
	update();
}

void DisplayWidget::save() {
	//
}

void DisplayWidget::initPageRect() {
	if (_current_frame == 0) { return; }
	_page_rects[_current_frame] = _page_rects[_current_frame - 1];
	updateFrame(_current_frame);
	update();
}

void DisplayWidget::showAnimation(QString str) {
	if (str == "none") {
		_show_animation = -1;
	}
	else {
		_show_animation = str.toInt();
	}
	update();
}

void DisplayWidget::loadFrame(int frame_id) {
	if (frame_id < _frames.size()) { return; }
	if (frame_id == _frames.size()) {

		printf("load frame %d\n", frame_id);

		Frame frame;

		//
		std::ostringstream ifname;
		ifname << frames_dir << "Layer " << (frame_id+1) << ".png";
		frame.img = cv::imread(ifname.str());

		std::ostringstream mask_name;
		mask_name << frames_dir << "Layer " << (frame_id + 1) << " mask.png";
		frame.mask = cv::imread(mask_name.str());

		_frames.push_back(frame);

		updateFrame(frame_id);
	}
	else {
		loadFrame(frame_id - 1);
	}
}

void transform(cv::Mat &bg, const std::string &file_name, float pos[][2]);
void applyMask(cv::Mat &dst, cv::Mat &src, cv::Mat &mask);

void DisplayWidget::updateFrame(int frame_id) {

	auto &frame = _frames[_current_frame];
	auto &page_rect = _page_rects[_current_frame];
	auto pos = page_rect.pos;

	frame.img.copyTo(frame.output);

	//
	transform(frame.output, leftPageFileName(), pos);
	transform(frame.output, rightPageFileName(), pos + 4);

	applyMask(frame.output, frame.img, frame.mask);
}

// -------- -------- -------- -------- -------- -------- -------- --------
void DisplayWidget::loadPageRects() {

	std::ostringstream rect_file_name;
	rect_file_name << frames_dir << "0_rect.txt";
	std::ifstream rect_fin(rect_file_name.str());

	for (int i = 0; i < n_frames; ++i) {

		int fid;
		rect_fin >> fid;

		PageRect pr;
		auto pos = pr.pos;
		for (int ip = 0; ip < 8; ++ip) {
			rect_fin >> pos[ip][0] >> pos[ip][1];
		}

		_page_rects.push_back(pr);

	}

}

void DisplayWidget::savePageRects() {

	std::ostringstream rect_file_name;
	rect_file_name << frames_dir << "0_rect.txt";
	std::ofstream rect_fout(rect_file_name.str());

	for (int i = 0; i < n_frames; ++i) {

		rect_fout << i+1 << std::endl << std::endl;

		auto &pr = _page_rects[i];
		auto pos = pr.pos;
		for (int ip = 0; ip < 4; ++ip) {
			rect_fout << pos[ip][0] << ' ' << pos[ip][1] << std::endl;
		}

		rect_fout << std::endl;

		for (int ip = 4; ip < 8; ++ip) {
			rect_fout << pos[ip][0] << ' ' << pos[ip][1] << std::endl;
		}

		rect_fout << std::endl;
	}

}

// -------- -------- -------- -------- -------- -------- -------- --------
void DisplayWidget::mousePressEvent(QMouseEvent *e) {

	auto &frame = _frames[_current_frame];
	auto &page_rect = _page_rects[_current_frame];
	auto pos = page_rect.pos;

	// mouse pos -> image pos
	float ix = e->pos().x() / (float)rect().width() * frame.img.cols;
	float iy = e->pos().y() / (float)rect().height() * frame.img.rows;

	//
	int idx = -1;
	float min_dis = 1e10;

	for (int i = 0; i < 8; ++i) {
		float px = pos[i][0];
		float py = pos[i][1];

		auto dx = px - ix;
		auto dy = py - iy;
		auto dis = dx*dx + dy*dy;

		if (dis < min_dis) {
			min_dis = dis;
			idx = i;
		}
	}

	if (idx != -1) {
		pos[idx][0] = ix;
		pos[idx][1] = iy;
	}

	//
	updateFrame(_current_frame);
	savePageRects();
	update();
}

//void DisplayWidget::mouseReleaseEvent(QMouseEvent *event) {
//}

void DisplayWidget::paintEvent(QPaintEvent *event) {
	auto &frame = _frames[_current_frame];

	QPainter painter(this);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);

	auto &img = frame.output;
	cv::Mat rimg;
	cv::cvtColor(img, rimg, cv::COLOR_BGR2RGB);
	QImage qimg(rimg.data, rimg.cols, rimg.rows, rimg.step, QImage::Format_RGB888);
	//QImage qimg(img.data, img.cols, img.rows, QImage::

	painter.drawImage(rect(), qimg);

	// 
	if (_show_animation != -1) {

		painter.setBrush(Qt::red);
		painter.setPen(Qt::green);

		auto iw = _frames[0].img.cols;
		auto ih = _frames[0].img.rows;

		auto ww = rect().width();
		auto wh = rect().height();

		for (int i = 0; i < n_frames; ++i) {
			float x = _page_rects[i].pos[_show_animation][0];
			float y = _page_rects[i].pos[_show_animation][1];

			x = x / iw * ww;
			y = y / ih * wh;

			painter.drawEllipse(QPointF(x, y), 3, 3);
		}
	}

}
