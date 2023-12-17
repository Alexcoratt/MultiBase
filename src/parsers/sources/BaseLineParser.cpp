#include <algorithm>
#include <sstream>
#include <iostream>

#include "BaseLineParser.hpp"
#include "split_string.h"
#include "TableException.hpp"

BaseLineParser::BaseLineParser(IValueParser * valueParser) : _valueParser(valueParser) {}
BaseLineParser::BaseLineParser(BaseLineParser const & other) : _valueParser(other._valueParser) {}
BaseLineParser & BaseLineParser::operator=(BaseLineParser const & other) {
	if (this != &other) {
		BaseLineParser tmp{other};
		swap(tmp);
	}
	return *this;
}

BaseLineParser::~BaseLineParser() {}
void BaseLineParser::swap(BaseLineParser & other) { std::swap(_valueParser, other._valueParser); }

IValueParser const * BaseLineParser::getValueParser() const { return _valueParser; }
IValueParser * BaseLineParser::getValueParser() { return _valueParser; }
void BaseLineParser::setValueParser(IValueParser * valueParser) { _valueParser = valueParser; }

std::map<std::string, AutoValue> BaseLineParser::parseLine(std::vector<std::string> const & headers, std::string const & line) const {
	unsigned int width;
	char ** parts;
	split_string_screened(line.c_str(), ',', '\"', &width, &parts);

	unsigned int headerCount = headers.size();
	if (width != headerCount && width != 0)
		throw TableException("headers array and row elements array have different sizes: " + std::to_string(headerCount) + " required and " + std::to_string(width) + " provided");

	std::map<std::string, AutoValue> res;
	for (unsigned int i = 0; i < width; ++i) {
		try {
			res[headers[i]] = _valueParser->parseValue(parts[i]);
		} catch (std::exception const & err) {
			std::cerr << err.what() << "\nWhile parsing line\n===\n" << line << "\n===\nValue being parsed: \"" << parts[i] << '\"' << std::endl;
			throw err;
		}
		free(parts[i]);
	}
	free(parts);
	return res;
}

std::string BaseLineParser::parseReverse(std::vector<std::string> const & headers, std::map<std::string, AutoValue> const & row) const {
	std::stringstream res;
	res << _valueParser->parseReverse(row.at(headers.at(0)));
	unsigned int width = headers.size();
	for (unsigned int i = 1; i < width; ++i)
		res << ',' << _valueParser->parseReverse(row.at(headers.at(i)));
	return res.str();
}
