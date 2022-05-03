#include "Widget.h"
#include "Button.h"
#include <QPainter>
#include <QMouseEvent>
#include <string>
#include <vector>
#include <QMessageBox>


Widget::Widget(std::string file_path) 
	: QWidget()
{
	this->resize(w, h);
	buttons = Read(file_path);
}

Widget::Widget(std::vector<Button> buttons, Widget *return_to) 
	: QWidget(), return_to(return_to)
{
	this->resize(w, h);
	this->buttons = buttons;
	this->buttons.emplace_back(Button("back", "", Button::Type::back));
}

void Widget::paintEvent(QPaintEvent *event) {
	QPainter painter(this);

	int n = buttons.size();
	int step = h / (n + 2);
	
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Draw(w/2 - buttons[i].w/2, step * (i + 1), &painter);
	}
}

void Widget::mousePressEvent(QMouseEvent *event) {
	QPointF pos = event->position();
	for (auto & button: buttons) {
		if (pos.x()>= button.x && pos.x() <= button.x + button.w && pos.y() >= button.y && pos.y() <= button.y + button.h) {
			switch(button.type) {
				case Button::Type::popup:
					buttonHandlerPopup(button.info);
					break;
				case Button::Type::none:
					buttonHandlerNone();
					break;
				case Button::Type::parent:
					buttonHandlerParent(button.submenu);
					break;
				case Button::Type::back:
					buttonHandlerBack();
					break;
			}
		}
	}
}

void Widget::buttonHandlerPopup(std::string message) {
	QMessageBox::information(this, "popup", message.c_str()); 
}

void Widget::buttonHandlerNone() {
	std::cout << "Click!\n";
}

void Widget::buttonHandlerParent(std::vector<Button> buttons) {
	Widget *submenu = new Widget(buttons, this); 
	this->close();
	submenu->show();
}

void Widget::buttonHandlerBack() {
	if (return_to != nullptr) {
		this->close();
		return_to->show();
	}
}

