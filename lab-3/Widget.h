#pragma once

#include "Button.h"
#include <QWidget>
#include <string>
#include <vector>


class Widget: public QWidget
{
public:
	Widget(std::string file_path);
	Widget(std::vector<Button> buttons, Widget* return_to = nullptr);

private:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void buttonHandlerNone();
	void buttonHandlerPopup(std::string message);
	void buttonHandlerBack();
	void buttonHandlerParent(std::vector<Button> buttons);

	std::vector<Button> buttons;
	Widget *return_to;
	int w = 500;
	int h = 500;
};
