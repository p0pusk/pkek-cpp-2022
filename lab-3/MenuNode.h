#pragma once

#include <iostream>
#include <string>
#include <vector>



class MenuNode
{
public:
	enum Type {
		parent,
		popup,
		color,
		none
	};

	std::string name;
	std::string info;
	Type type;
	std::vector<MenuNode> submenu;
};


std::vector<MenuNode> Read(std::string filePath);


