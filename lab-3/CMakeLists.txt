cmake_minimum_required(VERSION 3.14)
project(test)

find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

add_executable(
	test
	main.cpp
	MenuNode.cpp
	MenuWindow.cpp
	)

target_link_libraries(test Qt::Widgets)
