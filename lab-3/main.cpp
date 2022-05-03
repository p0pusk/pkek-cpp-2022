#include <iostream>
#include <QApplication>
#include <QtWidgets>
#include "Widget.h"


int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	Widget window("input.txt");
	window.show();

	return app.exec();
}
