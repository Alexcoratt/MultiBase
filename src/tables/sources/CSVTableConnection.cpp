#include <sstream>
#include <algorithm>

#include "CSVTableConnection.hpp"
#include "TableException.hpp"
#include "EndOfTableException.hpp"

#include "split_string.h"

AutoValue parseValue(std::string line) {
	return line;
}

std::string valueToCSV(AutoValue const & value) {
	return "\"" + (std::string)value + "\"";
}

std::map<std::string, AutoValue> CSVTableConnection::parseRow(std::vector<std::string> const & headers, std::string const & line) {
	unsigned int width;
	char ** parts;
	split_string(line.c_str(), ',', &width, &parts);

	if (width != headers.size())
		throw TableException("headers array and row elements array have different sizes");

	std::map<std::string, AutoValue> res;
	for (unsigned int i = 0; i < width; ++i) {
		res[headers[i]] = parseValue(parts[i]);
		free(parts[i]);
	}
	free(parts);
	return res;
}

std::string CSVTableConnection::rowToString(std::vector<std::string> const & headers, std::map<std::string, AutoValue> const & row) {
	std::stringstream res{valueToCSV(row.at(headers.at(0)))};
	unsigned int width = headers.size();
	for (unsigned int i = 1; i < width; ++i)
		res << ',' << valueToCSV(row.at(headers.at(i)));
	res << '\n';
	return res.str();
}

bool quotesClosed(std::string const & line) {
	bool res = true;
	for (char symb : line)
		if (symb == '\"')
			res = !res;
	return res;
}

std::string CSVTableConnection::readNextRow(std::istream & input) {
	std::string line;
	std::getline(input, line);
	if (quotesClosed(line))
		return line;

	std::string addition;
	while (std::getline(input, addition) && quotesClosed(addition)) {
		line.push_back('\n');
		line.append(addition);
	}
	line.push_back('\n');
	line.append(addition);
	return line;
}

void CSVTableConnection::skipNextRows(std::istream & input, std::size_t rowCount) {
	bool quotesClosed = true;
	char symb;
	while(rowCount--) {
		if (input.eof())
			throw EndOfTableException("CSVTableConnection");
		while ((symb = input.get()) != '\n' && quotesClosed) {
			if (symb == '\"')
				quotesClosed = !quotesClosed;
		}
	}
}

// private methods

CSVTableConnection::CSVTableConnection(std::string const & filename) : _filename{filename} {}
CSVTableConnection::CSVTableConnection(CSVTableConnection const & other) : _filename{other._filename} {}
CSVTableConnection & CSVTableConnection::operator=(CSVTableConnection const & other) {
	if (this != &other) {
		CSVTableConnection tmp(other);
		swap(tmp);
	}
	return *this;
}

CSVTableConnection::~CSVTableConnection() {}

void CSVTableConnection::swap(CSVTableConnection & other) {
	std::swap(_filename, other._filename);
}

std::vector<std::string> CSVTableConnection::getHeaders() const {
	std::string line;
	std::ifstream file(_filename);
	std::getline(file, line);
	file.close();

	unsigned int count;
	char ** headers;
	split_string(line.c_str(), ',', &count, &headers);
	std::vector<std::string> res{count};
	for (unsigned int i = 0; i < count; ++i) {
		res[i] = headers[i];
		free(headers[i]);
	}
	free(headers);
	return res;
}

std::size_t CSVTableConnection::getWidth() const {
	std::string line;
	std::ifstream file(_filename);
	std::getline(file, line);
	file.close();

	return count_char(line.c_str(), ',') + 1;
}

std::size_t CSVTableConnection::getHeight() const {
	std::ifstream file(_filename);
	try {
		skipNextRows(file);
	} catch (EndOfTableException const &) {
		throw TableException("CSV File has no headers");
	}
	std::size_t res = 0;
	while (true) {
		try {
			skipNextRows(file);
			++res;
		} catch (EndOfTableException const &) {
			return res;
		}
	}
}

std::map<std::string, AutoValue> CSVTableConnection::getRow(std::size_t const & index) const {
	std::ifstream file(_filename);
	skipNextRows(file, index + 1);
	return parseRow(getHeaders(), readNextRow(file));
}

void CSVTableConnection::insertRow(std::map<std::string, AutoValue> const & row, std::size_t const & index) {
	throw std::runtime_error("CSVTableConnection::insertRow: coming soon");
}

void CSVTableConnection::appendRow(std::map<std::string, AutoValue> const & row) {
	throw std::runtime_error("CSVTableConnection::appendRow: coming soon");
}

void CSVTableConnection::updateRow(std::map<std::string, AutoValue> const & row, std::size_t const & index) {
	throw std::runtime_error("CSVTableConnection::updateRow: coming soon");
}

void CSVTableConnection::removeRow(std::size_t const & index) {
	throw std::runtime_error("CSVTableConnection::removeRow: coming soon");
}

CSVTableConnectionIterator * CSVTableConnection::getIterator() {
	return new CSVTableConnectionIterator(this);
}
