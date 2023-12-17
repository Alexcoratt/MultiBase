#ifndef I_VALUE_PARSER_HPP
#define I_VALUE_PARSER_HPP

#include <string>
#include <AutoValue.hpp>

class IValueParser {
public:
	virtual ~IValueParser() {}

	virtual AutoValue parseValue(std::string const & value) const = 0;
	virtual AutoValue parseValue(std::string const & value) { return ((IValueParser const *)this)->parseValue(value); }

	virtual std::string parseReverse(AutoValue const & value) const = 0;
};

#endif
