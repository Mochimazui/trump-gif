#ifndef TRUMPGIFMAINWINDOW_H
#define TRUMPGIFMAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_trumpgifmainwindow.h"

class TrumpGIFMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	TrumpGIFMainWindow(QWidget *parent = 0);
	~TrumpGIFMainWindow();

public slots:
	void updateFrameID(int);

private:
	Ui::TrumpGIFMainWindowClass ui;
};

#endif // TRUMPGIFMAINWINDOW_H
