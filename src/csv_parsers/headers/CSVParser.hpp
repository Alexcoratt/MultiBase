#ifndef CSV_PARSER_HPP
#define CSV_PARSER_HPP

#include <fstream>
#include <string>
#include <map>

using iterator = std::iterator<std::input_iterator_tag, std::map<std::string, std::string>>;

class CSVParser {
private:
	std::string const _filename;
	std::ifstream * _file;

public:
	CSVParser(std::string const & filename);
	~CSVParser();

	std::map<std::string, std::string> getRow(std::size_t const & lineNumber) const;
	iterator begin() const;
	iterator end() const;
};

#endif
