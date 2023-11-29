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

// TODO: add shielding of commas inside quotes
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

template <typename T>
constexpr void printVector(std::vector<T> const & values, char const * endline = "\n", std::ostream & out = std::cout) {
	for (auto const & value : values)
		out << value << endline;
}

int main(int argc, char ** argv) {

	char const * filename = FILENAME;
	if (argc > 1)
		filename = argv[1];
	else
		std::cerr << "Filename is not entered\nUsing default filename: " << filename << std::endl;

	std::ifstream file(filename);
	if (!file.good()) {
		std::cerr << "Error occured while opening file " << filename << std::endl;
		return -1;
	}

	std::string line = getNextRow(file);
	std::size_t count = 0;

	while (!file.eof()) {
		//std::cout << line << '\n';
		auto parts = split(line, ',');

		printVector(parts);

		line = getNextRow(file);

		if (count++ == 5)
			break;
	}
	return 0;
}
