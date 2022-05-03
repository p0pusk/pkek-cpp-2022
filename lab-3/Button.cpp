#include "Button.h"
#include <fstream>


Button::Button() {

}


Button::Button(std::string name, std::string info, Button::Type type, std::vector<Button> submenu) 
	: name(name), info(info), type(type), submenu(submenu)
{

}


void Button::Draw(int x, int y, QPainter *painter) {
	this->x = x;
	this->y = y;
	painter->setBrush(QBrush(Qt::gray, Qt::SolidPattern));
	painter->drawRect(QRectF(x, y, w, h));
	painter->drawText(QRectF(x, y, w, h), Qt::AlignCenter, QString(name.c_str()));
}


std::vector<Button> Read(std::string filePath) {
	std::fstream file(filePath);

	if (!file) {
		std::cerr << "file open failed: " << std::strerror(errno) << "\n";
	}

	std::istream_iterator<std::string> iter(file);
	std::istream_iterator<std::string> eos;
	bool submenu = false;
	Button *curMenu = nullptr;
	Button *curSub = nullptr;
	std::vector<Button> readedNodes;
	while (iter != eos) {
		if (*iter == "{") {
			if (submenu) {
				curSub = new Button;
			}
			else {
				curMenu = new Button;
			}
		}

		if (*iter == "name:") {
			iter++;
			if (submenu) {
				curSub->name = *iter;
			}
			else {
				curMenu->name = *iter;
			}
		}
		if (*iter == "info:") {
			iter++;
			if (submenu) {
				curSub->info = *iter;
			}
			else {
				curMenu->info = *iter;
			}
		}
		if (*iter == "type:") {
			iter++;
			Button::Type type;
			if (*iter == "popup") type = Button::Type::popup;
			else if (*iter == "parent") type = Button::Type::parent;
			else type = Button::Type::none;

			if (submenu) {
				curSub->type = type;
			}
			else {
				curMenu->type = type;
			}
		}
		if (*iter == "submenus:") {
			submenu = true;
		}
		if (*iter == "}") {
			if (submenu) {
				submenu = false;
				curMenu->submenu.emplace_back(*curSub);
			}
			else {
				readedNodes.emplace_back(*curMenu);
			}
		}
		if (*iter == "},") {
			if (submenu) {
				curMenu->submenu.emplace_back(*curSub);
			}
			else {
				readedNodes.emplace_back(*curMenu);
			}
		}
		iter++;
	}

	std::cout << "Reading menus file: " << std::endl;
	
	for (auto & men: readedNodes) {
		std::cout << "----------------" << std::endl;
		std::cout << "name: " << men.name << std::endl;
		std::cout << "type: " << men.type << std::endl;
		std::cout << "info: " << men.info << std::endl;
		for (auto & sub : men.submenu) {
			std::cout << "----------------" << std::endl;
			std::cout << "\tsubmenu name: " << sub.name << std::endl;
			std::cout << "\tsubmenu type: " << sub.type << std::endl;
			std::cout << "\tsubmenu info: " << sub.info << std::endl;
		}
	}
	std::cout << std::endl;

	return readedNodes;
}
