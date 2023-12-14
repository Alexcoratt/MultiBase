#include "CSVTableConnection.hpp"
#include "TableException.hpp"

#include "split_string.h"

AutoValue parseValue(std::string line) {
	return line;
}

std::map<std::string, AutoValue> CSVTableConnection::parseRow(std::vector<std::string> const & headers, std::string const & line) {
	unsigned int width;
	char ** parts;
	split_string(line.c_str(), ',', &width, &parts);

	if (width != headers.size())
		throw TableException("headers array and row elements array have different sizes");

	std::map<std::string, AutoValue> res;
	for (unsigned int i = 0; i < width; ++i)
		res[headers[i]] = parseValue(parts[i]);
	return res;
}


