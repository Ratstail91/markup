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
	markup["a"] = "<b>foobar</b>";

	//it accepts it's own output
	std::cout << Markup(markup.ToString()).ToString() << std::endl;

	return 0;
}