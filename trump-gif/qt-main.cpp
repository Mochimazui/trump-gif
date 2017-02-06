
#include <QtWidgets/QApplication>
#include "trumpgifmainwindow.h"

int trump_gif_main(int argc, char *argv[]);

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	TrumpGIFMainWindow main_window;
	main_window.show();

	auto ret = app.exec();

	trump_gif_main(argc, argv);

	return ret;
}
