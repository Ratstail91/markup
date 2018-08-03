#include "markup.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
	//load the file
	std::ifstream is("tilemap.mu");
	std::stringstream buffer;

	buffer << is.rdbuf();

	Markup markup = buffer.str();

	//modify the markup
	markup["a"]["b"]["c"] = "hello world";
	markup["a"] = "<a><b><d>foobar</d></b></a>";

	//it accepts it's own output
	std::cout << Markup(markup.ToString()).ToString() << std::endl;

/*	Markup markup1("<hello><world>foobar</world></hello>");
	std::string foobar = markup1["world"].GetAttribute("_value");

	Markup markup2;
	markup2 = "<outertag><tag>str</tag></outertag>";
	std::string str = markup2["tag"].GetAttribute("_value");

	std::cout << markup2.ToString() << std::endl;
*/
	return 0;
}