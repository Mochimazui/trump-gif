#include "trumpgifmainwindow.h"

TrumpGIFMainWindow::TrumpGIFMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.previousButton, SIGNAL(clicked()), ui.displayWidget, SLOT(priviousFrame()));
	connect(ui.nextButton, SIGNAL(clicked()), ui.displayWidget, SLOT(nextFrame()));
	connect(ui.saveButton, SIGNAL(clicked()), ui.displayWidget, SLOT(save()));
	connect(ui.initButton, SIGNAL(clicked()), ui.displayWidget, SLOT(initPageRect()));

	ui.animationComboBox->addItem("none");
	for (int i = 0; i < 8; ++i) {
		ui.animationComboBox->addItem(QString::number(i));
	}

	connect(ui.animationComboBox, SIGNAL(activated(QString)), ui.displayWidget, SLOT(showAnimation(QString)));

	connect(ui.displayWidget, SIGNAL(updateFrameID(int)), this, SLOT(updateFrameID(int)));
}

TrumpGIFMainWindow::~TrumpGIFMainWindow()
{

}

void TrumpGIFMainWindow::updateFrameID(int id) {
	ui.label->setText(QString::number(id));
}
