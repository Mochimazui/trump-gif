#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

#include <vector>

#include <opencv2/opencv.hpp>

// -------- -------- -------- -------- -------- -------- -------- --------
struct Frame {
	cv::Mat img;
	cv::Mat mask;
	cv::Mat output;
};

struct PageRect {
	float pos[8][2];
};

// -------- -------- -------- -------- -------- -------- -------- --------
class DisplayWidget : public QWidget
{
	Q_OBJECT

public:
	DisplayWidget(QWidget *parent);
	~DisplayWidget();

signals:
	void updateFrameID(int id);

public slots:
	void priviousFrame();
	void nextFrame();

	void save();
	void initPageRect();

	void showAnimation(QString);

protected:

	void mousePressEvent(QMouseEvent *event);
	//void mouseReleaseEvent(QMouseEvent *event);

	void paintEvent(QPaintEvent *event);

private:
	void loadFrame(int frame_id);
	void updateFrame(int frame_id);

	void loadPageRects();
	void savePageRects();

private:

	int _current_frame = 0;
	std::vector<Frame> _frames;
	std::vector<PageRect> _page_rects;

	int _show_animation = -1;

	cv::Mat _left_page;
	cv::Mat _right_page;

};

#endif // DISPLAYWIDGET_H
