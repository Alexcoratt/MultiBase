#ifndef BASE_VALUE_PARSER_HPP
#define BASE_VALUE_PARSER_HPP

#include "IValueParser.hpp"

class BaseValueParser : public IValueParser {
public:
	AutoValue parseValue(std::string const & value) const override { return value; }
	std::string parseReverse(AutoValue const & value) const override { return (std::string)value; }
};

#endif
