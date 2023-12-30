#ifndef TABLE_TYPES_HPP
#define TABLE_TYPES_HPP

#include <map>
#include <string>

#include <AutoValue.hpp>

class SmartTableIterator;

namespace multi_base_types {
	typedef std::map<std::string, AutoValue> table_row;
	typedef SmartTableIterator iterator;
}

#endif
