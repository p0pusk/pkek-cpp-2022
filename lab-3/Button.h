#pragma once

#include <iostream>
#include <string.h>
#include <QPainter>
#include <vector>

class Button 
{
public:
	enum Type {
		parent,
		popup,
		back,
		none
	};

	Button();
	Button(std::string name, std::string info, Button::Type type, std::vector<Button> submenu = std::vector<Button>(0));
	void Draw(int w, int h, QPainter *painter);

	std::string name;
	std::string info;
	Type type;
	std::vector<Button> submenu;
	int w = 100;
	int h = 50;
	int x;
	int y;

private:
	QPainter *painter;

};

std::vector<Button> Read(std::string filePath);

