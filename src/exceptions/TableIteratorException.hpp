#ifndef TABLE_ITERATOR_EXCEPTION_HPP
#define TABLE_ITERATOR_EXCEPTION_HPP

#include <stdexcept>

class TableIteratorException : public std::exception {
public:
	char const * what() const noexcept override { return "TableIteratorException"; }
};

#endif
