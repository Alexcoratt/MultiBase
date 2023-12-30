#ifndef I_TABLE_ITERATOR_HPP
#define I_TABLE_ITERATOR_HPP

#include "table_types.hpp"

class ITableIterator {
public:
	virtual ~ITableIterator() {}

	virtual ITableIterator * getClone() const = 0;

	virtual void first() = 0;
	virtual void next() = 0;
	virtual multi_base_types::table_row get() { return ((ITableIterator const *)this)->get(); }
	virtual multi_base_types::table_row get() const = 0;
	virtual bool isEnd() const = 0;

	// inserts a row before current position
	virtual void insert(multi_base_types::table_row const &) = 0;

	virtual void update(multi_base_types::table_row const &) = 0;
	virtual void remove() = 0;
};

#endif
