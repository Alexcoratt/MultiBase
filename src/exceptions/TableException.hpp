#ifndef TABLE_EXCEPTION_HPP
#define TABLE_EXCEPTION_HPP

#include <stdexcept>

class TableException : public std::exception {
private:
	std::string _msg;
public:
	TableException() {}
	explicit TableException(std::string const & msg) { _msg = getExceptionName() + ": " + msg; }
	virtual std::string getExceptionName() const { return "TableException"; }

	char const * what() const noexcept override { return _msg.c_str(); }
};

#endif
