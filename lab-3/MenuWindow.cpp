#include <QMessageBox>
#include <QGuiApplication>
#include <QPalette>
#include <cstddef>
#include <cstdlib>
#include "MenuWindow.h"
#include "MenuNode.h"


MenuWindow::MenuWindow(std::vector<MenuNode> menus, QWidget *return_to)
	: QWidget()
{
	this->resize(500, 500);
	layout = new QVBoxLayout(this);
	for (auto & men: menus) {
		QPushButton* button = new QPushButton(men.name.c_str(), this); 
		button->resize(250, 100);
		if (men.type == MenuNode::Type::parent) {
			MenuWindow* newSub = new MenuWindow(men.submenu, this);
		submenus.push_back(newSub);
			connect(button, &QPushButton::released, this, &MenuWindow::buttonHandlerSubmenu);
		}
		else if (men.type == MenuNode::Type::popup) {
			connect(button, &QPushButton::released, this, &MenuWindow::buttonHandlerPopup);
		}
		else if (men.type == MenuNode::Type::color) {
			connect(button, &QPushButton::released, this, &MenuWindow::buttonHandlerColor);
		}
		else {
			connect(button, &QPushButton::released, this, &MenuWindow::buttonHandlerNone);
		}

		buttons.push_back(button);
		layout->addWidget(button);
	}

	if (return_to != nullptr) {
		this->return_to = return_to;
		QPushButton* button = new QPushButton("back", this); 
		button->resize(250, 200);
		connect(button, &QPushButton::released, this, &MenuWindow::buttonHandlerReturn);
		layout->addWidget(button);
	}
}


void MenuWindow::buttonHandlerSubmenu() {
	this->close();
	submenus.back()->show();
}

void MenuWindow::buttonHandlerPopup() {
	QMessageBox::information(this, "popup", "Popup!"); 
}

void MenuWindow::buttonHandlerNone() {
	std::cout << "Click!\n";
}

void MenuWindow::buttonHandlerColor() {
	QPalette pal = this->palette();
	pal.setColor(QPalette::Window, std::rand() % 7);
	this->setPalette(pal);
}

void MenuWindow::buttonHandlerReturn() {
	this->close();
	return_to->show();
}


