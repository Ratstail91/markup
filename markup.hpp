#pragma once

#include <map>
#include <string>

class Markup {
public:
	Markup() = default;
	Markup(std::string str);
	Markup& operator[](std::string str);
	Markup& operator=(std::string str);

	std::string ToString();
	int FromString(std::string str);
	bool IsLeaf();

private:
	std::map<std::string, Markup> nodeMap;
	std::map<std::string, std::string> attributes;
};
