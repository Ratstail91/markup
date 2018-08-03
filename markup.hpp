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
#pragma once

#include <map>
#include <string>

#define MU_NAME "__name"
#define MU_VALUE "__value"

class Markup {
public:
	Markup();
	Markup(std::string str);

	//access the sub-node "str"
	Markup& operator[](std::string str);

	//if valid markup, add it as a child. Otherwise, set it as _value
	Markup& operator=(std::string str);

	//print this markup tree as a string
	std::string ToString();

	//parse a string as markup
	int FromString(std::string str);

	//has no children
	bool IsLeaf();

	//access the attribute map
	//NOTE: _name and _value are reserved keys
	std::string GetAttribute(std::string key);
	std::string SetAttribute(std::string key, std::string val);

private:
	friend void mergeNodeTrees(Markup& dest, Markup src);

	std::map<std::string, Markup> nodeMap;
	std::map<std::string, std::string> attributes;
};
