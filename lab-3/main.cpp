#include <iostream>
#include <QApplication>
#include <QtWidgets>
#include <vector>
#include "MenuNode.h"
#include "MenuWindow.h"


int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	std::vector<MenuNode> data = Read("input.txt");
	MenuWindow window(data);

	window.show();


	return app.exec();
}
