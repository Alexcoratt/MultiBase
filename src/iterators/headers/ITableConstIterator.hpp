#ifndef I_TABLE_CONST_ITERATOR_HPP
#define I_TABLE_CONST_ITERATOR_HPP

#include "table_types.hpp"

class ITableConstIterator {
public:
	virtual ~ITableConstIterator() {}

	virtual ITableConstIterator * getClone() const = 0;

	virtual void first() = 0;
	virtual void next() = 0;
	virtual multi_base_types::table_row get() { return ((ITableConstIterator const *)this)->get(); }
	virtual multi_base_types::table_row get() const = 0;
	virtual bool isEnd() const = 0;
};

#endif
