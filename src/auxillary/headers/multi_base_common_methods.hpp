#ifndef MULTI_BASE_COMMON_METHODS_HPP
#define MULTI_BASE_COMMON_METHODS_HPP

#include <iostream>
#include <ITable.hpp>

namespace table_methods {
	void copyTable(ITable const * source, ITable * dest);
	void printTable(ITable const * table, std::ostream & out = std::cout);
}

#endif
