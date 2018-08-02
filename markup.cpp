#include "markup.hpp"

#include <cctype>
#include <sstream>
#include <stdexcept>
#include <vector>

//utilities
std::vector<std::string> splitString(std::string str, char delim) {
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

std::string chomp(std::string& str) {
	std::string chompable = " \n\r\t";
	str.erase(0, str.find_first_not_of(chompable));
	str.erase(str.find_last_not_of(chompable)+1);
	return str;
}

bool grind(std::string& str) {
	/* This function is a custom solution.
	 * It will remove most whitespace characters, but will allow
	 * a single space character to remain when found.
	 * HOWEVER if the first characters are spaces, it will remove
	 * them all and return true.
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
	bool ret = isspace(str[0]);
	str = result;
	return ret;
}

Markup::Markup(std::string str) {
	FromString(str);
}

Markup& Markup::operator[](std::string str) {
	//generate and access this sub-node
	return nodeMap[str];
}

Markup& Markup::operator=(std::string str) {
	FromString(str);
	return *this;
}

std::string Markup::ToString() {
	std::string result;

	if (IsLeaf()) {
		return attributes["_value"];
	}

	result += "<" + attributes["_name"];

	//print the attributes
	for (auto att : attributes) {
		if (att.first == "_name") {
			continue;
		}
		result += " " + att.first + "=\"" + att.second + "\"";
	}

	result += ">";

	//fill with all children
	for (auto it : nodeMap) {
		result += it.second.ToString();
	}

	//end this node
	result += "</" + attributes["_name"] + ">";
	
	return result;
}

int Markup::FromString(std::string str) {
	//remove whitespace
	bool chomped = grind(str);

	//ignore blanks
	if (!str.size()) {
		return 1;
	}

	//this node is a leaf
	if (str[0] != '<') {
		attributes["_name"] = "_leaf";
		attributes["_value"] = str;
		return str.size();
	}

	//get the open tag (without braces, with attributes)
	std::string openTag = str.substr(1, str.find('>') - 1);

	//truncate the open tag from str
	str = str.substr(openTag.size() + 2, std::string::npos);

	//get the open tag as attributes
	std::vector<std::string> attr = splitString(openTag, ' ');

	//save the attributes
	attributes["_name"] = attr[0];
	for (int i = 1; i < attr.size(); i++) {
		std::vector<std::string> pair = splitString(attr[i], '=');

		attributes[pair[0]] = pair[1].substr(1, pair[1].size() - 2);
	}

	//get the closing tag position
	int closingTagPos = str.find(std::string() + "</" + attr[0] + ">");
	int nextSiblingPos = closingTagPos + attr[0].size() + 3 + openTag.size() + 2 + chomped;

	//get the child string
	std::string childStr = str.substr(0, closingTagPos);

	int nextPos;
	do {
		//recurse to a temp node
		Markup tmpNode;
		nextPos = tmpNode.FromString(childStr);
		std::string name = tmpNode.attributes["_name"];

		//save the data from the temp node
		nodeMap[name] = tmpNode;
//		nodeMap[name].attributes.erase("_name"); //WARNING: Name is stored in two places

		//delete the processed node from the string
		childStr = childStr.substr(nextPos, std::string::npos);
	} while(childStr.size());

	return nextSiblingPos;
}

bool Markup::IsLeaf() {
	return !nodeMap.size();
}
