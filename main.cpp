#include "markup.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
	std::ifstream is("tilemap.mu");
	std::stringstream buffer;

	buffer << is.rdbuf();

	Markup markup = buffer.str();

	std::cout << markup.ToString() << std::endl;

	std::cout << markup["graphics"]["tile"]["h"]["_leaf"].ToString() << std::endl;

	return 0;
}