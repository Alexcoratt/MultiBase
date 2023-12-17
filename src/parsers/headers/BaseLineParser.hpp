#ifndef BASE_LINE_PARSER_HPP
#define BASE_LINE_PARSER_HPP

#include "ILineParser.hpp"
#include "IValueParser.hpp"

class BaseLineParser : public ILineParser {
private:
	IValueParser * _valueParser;

public:
	BaseLineParser(IValueParser * valueParser);
	BaseLineParser(BaseLineParser const & other);
	BaseLineParser & operator=(BaseLineParser const & other);
	~BaseLineParser();

	void swap(BaseLineParser & other);

	IValueParser const * getValueParser() const;
	IValueParser * getValueParser();
	void setValueParser(IValueParser * valueParser);

	std::map<std::string, AutoValue> parseLine(std::vector<std::string> const & headers, std::string const & line) const override;

	std::string parseReverse(std::vector<std::string> const & headers, std::map<std::string, AutoValue> const & row) const override;
};

#endif
