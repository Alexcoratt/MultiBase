#ifndef UNABLE_TO_CONNECT_EXCEPTION_HPP
#define UNABLE_TO_CONNECT_EXCEPTION_HPP

#include "TableConnectionException.hpp"

class UnableToConnectException : public TableConnectionException {
public:
	UnableToConnectException(std::string connName) : TableConnectionException("unable to connect to \"" + connName + "\"") {}
	std::string getExceptionName() const override { return "UnableToConnectException"; }
};

#endif
