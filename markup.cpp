/* Copyright: (c) Kayne Ruse 2018
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/
#include "markup.hpp"

#include <cctype>
#include <sstream>
#include <stdexcept>
#include <vector>

//utilities
static std::vector<std::string> splitString(std::string str, char delim) {
	std::vector<std::string> result;
	std::istringstream iss(str);
	std::string tmp;
	while(getline(iss, tmp, delim)) {
		if (tmp.size()) {
			result.push_back(tmp);
		}
	}
	return result;
}

static std::string chomp(std::string str) {
	std::string chompable = " \n\r\t";
	str.erase(0, str.find_first_not_of(chompable));
	str.erase(str.find_last_not_of(chompable)+1);
	return str;
}

static std::string grind(std::string str) {
	/* This function is a custom solution.
	 * It will remove most whitespace characters, but will allow
	 * a single space character to remain when found except at the
	 * beginning and end.
	*/
	std::string result;
	bool space = true; //remove leading spaces

	for (auto it : str) {
		if (isspace(it)) {
			if (!space && it == ' ') {
				space = true;
				result += it;
			}
		} else {
			result += it;
			space = false;
		}
	}
	return chomp(result);
}

void mergeNodeTrees(Markup& dest, Markup src) {
	for(auto& it : src.attributes) {
		dest.attributes[it.first] = it.second;
	}

	for (auto it : src.nodeMap) {
		mergeNodeTrees(dest[it.first], it.second);
	}
}

Markup::Markup() {
	//placeholder super tag
	attributes[MU_NAME] = "markup";
}

Markup::Markup(std::string str) {
	FromString(str);
}

Markup& Markup::operator[](std::string str) {
	//generate and access this sub-node
	nodeMap[str].attributes[MU_NAME] = str;
	return nodeMap[str];
}

Markup& Markup::operator=(std::string str) {
	str = grind(str);
	if (str[0] == '<') {
		Markup tmp(str);
//		mergeNodeTrees(*this, Markup("<" + attributes[MU_NAME] + ">" + tmp.ToString() + "</" + attributes[MU_NAME] + ">"));
		mergeNodeTrees(*this, tmp);
	} else {
		attributes[MU_VALUE] = str;
	}
	return *this;
}

std::string Markup::ToString() {
	std::string result;

	result += "<" + attributes[MU_NAME];
	//print the attributes
	for (auto att : attributes) {
		if (att.first == MU_NAME || att.first == MU_VALUE) {
			continue;
		}
		result += " " + att.first + "=\"" + att.second + "\"";
	}

	result += ">";
	if (IsLeaf()) {
		result += attributes[MU_VALUE];
	} else {
		//fill with all children
		for (auto it : nodeMap) {
			result += it.second.ToString();
		}
	}
	//end this node
	result += "</" + attributes[MU_NAME] + ">";
	return result;
}

int Markup::FromString(std::string str) {
	//count the chomped amount (for the siblings)
	int chompedAmount = str.size() - grind(str).size();

	//remove most whitespace
	str = grind(str);

	//get the open tag (without braces, with attributes)
	std::string openTag = str.substr(1, str.find('>') - 1);
	//truncate the open tag from str
	str = str.substr(openTag.size() + 2, std::string::npos);
	//get the open tag as attributes
	std::vector<std::string> attr = splitString(openTag, ' ');

	//save the attributes
	attributes[MU_NAME] = attr[0];
	for (int i = 1; i < attr.size(); i++) {
	
		std::vector<std::string> pair = splitString(attr[i], '=');

		//TODO: ensure the attribute integrity

		attributes[pair[0]] = pair[1].substr(1, pair[1].size() - 2); //substr here to strip the quote marks
	}

	//get the closing tag position
	int closingTagPos = str.find(std::string() + "</" + attr[0] + ">");
	int nextSiblingPos = closingTagPos + attr[0].size() + 3 + openTag.size() + 2 + chompedAmount;

	//get the child string
	std::string childStr = str.substr(0, closingTagPos);

	//this node is a leaf
	std::string tmpStr = grind(childStr);
	if (tmpStr[0] != '<') {
		attributes[MU_VALUE] = childStr;
		return nextSiblingPos;
	}
	//read each child node
	int nextPos;
	do {
		//recurse to a temp node
		Markup tmpNode;
		nextPos = tmpNode.FromString(childStr);
		std::string name = tmpNode.attributes[MU_NAME];

		//save the data from the temp node
		nodeMap[name] = tmpNode;
//		nodeMap[name].attributes.erase(MU_NAME); //WARNING: Name is stored in two places

		//delete the processed node from the string
		childStr = childStr.substr(nextPos, std::string::npos);
	} while(childStr.size());

	return nextSiblingPos;
}

bool Markup::IsLeaf() {
	return !nodeMap.size();
}

std::string Markup::GetAttribute(std::string key) {
	return attributes[key];
}

std::string Markup::SetAttribute(std::string key, std::string val) {
	return attributes[key] = val;
}