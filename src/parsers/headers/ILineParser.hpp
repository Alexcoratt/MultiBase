#ifndef I_LINE_PARSER_HPP
#define I_LINE_PARSER_HPP

#include <map>
#include <vector>
#include <string>
#include <AutoValue.hpp>

class ILineParser {
public:
	virtual ~ILineParser() {}

	virtual std::map<std::string, AutoValue> parseLine(std::vector<std::string> const & headers, std::string const & line) const = 0;
	virtual std::map<std::string, AutoValue> parseLine(std::vector<std::string> const & headers, std::string const & line) { return ((ILineParser const *)this)->parseLine(headers, line); }

	virtual std::string parseReverse(std::vector<std::string> const & headers, std::map<std::string, AutoValue> const & row) const = 0;
};

#endif
