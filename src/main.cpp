#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include <AutoValue.hpp>

#define FILENAME "data/backloggd_games.csv"

bool quotesClosed(std::string const & line) {
	bool res = true;
	for (char symb : line)
		if (symb == '\"')
			res = !res;
	return res;
}

std::string getNextRow(std::ifstream & csvStream) {
	std::string line;
	std::getline(csvStream, line);
	if (quotesClosed(line))
		return line;

	std::string addition;
	while (std::getline(csvStream, addition) && quotesClosed(addition)) {
		line.push_back('\n');
		line.append(addition);
	}
	line.push_back('\n');
	line.append(addition);
	return line;
}

std::vector<std::string> split(std::string const & line, char delimiter = ' ') {
	std::vector<std::string> res;
	std::size_t left = 0;
	std::size_t right = line.find(delimiter);

	while (right != std::string::npos) {
		if (left <= right)
			res.push_back(line.substr(left, right - left));
		left = right + 1;
		right = line.find(delimiter, left);
	}

	if (left < line.size())
		res.push_back(line.substr(left));

	return res;
}

int main(int argc, char ** argv) {
	std::ifstream file(FILENAME);
	std::string line = getNextRow(file);

	std::size_t count = 0;

	while (!file.eof() && count++ < 5) {
		std::cout << line << '\n';
		auto parts = split(line, ',');
		for (auto part : parts)
			std::cout << '\"' << part << '\"' << '\n';
		std::cout << '\n';

		line = getNextRow(file);
	}

	return 0;
}
