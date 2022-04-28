#include "MenuNode.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <type_traits>
#include <vector>
#include <QtWidgets>

using namespace std;


std::vector<MenuNode> Read(std::string filePath) {
	std::fstream file(filePath);

	if (!file) {
		std::cerr << "file open failed: " << std::strerror(errno) << "\n";
	}

	std::istream_iterator<std::string> iter(file);
	std::istream_iterator<std::string> eos;
	bool submenu = false;
	MenuNode *curMenu = nullptr;
	MenuNode *curSub = nullptr;
	std::vector<MenuNode> readedNodes;
	while (iter != eos) {
		if (*iter == "{") {
			if (submenu) {
				curSub = new MenuNode;
			}
			else {
				curMenu = new MenuNode;
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
			MenuNode::Type type;
			if (*iter == "popup") type = MenuNode::Type::popup;
			else if (*iter == "color") type = MenuNode::Type::color;
			else if (*iter == "parent") type = MenuNode::Type::parent;
			else type = MenuNode::Type::none;

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

