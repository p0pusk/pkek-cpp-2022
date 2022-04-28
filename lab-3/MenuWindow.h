#pragma once

#include "MenuNode.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>


class MenuWindow : public QWidget
{
public:
	MenuWindow(std::vector<MenuNode> menus, QWidget *return_to = nullptr);

protected:
	virtual void buttonHandlerSubmenu();
	virtual void buttonHandlerPopup();
	virtual void buttonHandlerNone();
	virtual void buttonHandlerColor();
	virtual void buttonHandlerReturn();

private:
	QWidget *return_to;
	QVBoxLayout *layout = new QVBoxLayout();
	std::vector<QPushButton*> buttons; 
	std::vector<MenuWindow*> submenus;
};

