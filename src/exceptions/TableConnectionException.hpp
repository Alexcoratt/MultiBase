#ifndef TABLE_CONNECTION_EXCEPTION_HPP
#define TABLE_CONNECTION_EXCEPTION_HPP

#include "TableException.hpp"

class TableConnectionException : public TableException {
public:
	TableConnectionException() {}
	explicit TableConnectionException(std::string const & msg) : TableException(msg) {}
	std::string getExceptionName() const override { return "TableConnectionException"; }
};

#endif
