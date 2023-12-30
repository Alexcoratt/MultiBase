#ifndef MULTI_BASE_COMMON_METHODS_HPP
#define MULTI_BASE_COMMON_METHODS_HPP

#include <iostream>
#include <ITable.hpp>

namespace table_methods {
	void copyTable(ITable * source, ITable * dest);
	void printTable(ITable * table, std::ostream & out = std::cout);
}

#endif
