#ifndef END_OF_TABLE_EXCEPTION_HPP
#define END_OF_TABLE_EXCEPTION_HPP

#include <string>
#include "TableIteratorException.hpp"

class EndOfTableException : public TableIteratorException {
private:
	std::string _msg;

public:
	EndOfTableException(std::string const & tableName) : _msg("EndOfTableException: end of table \"" + tableName + "\" encountered") {}

	char const * what() const noexcept override { return _msg.c_str(); }
};

#endif
