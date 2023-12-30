#ifndef I_TABLE_ITERATOR_HPP
#define I_TABLE_ITERATOR_HPP

#include "ITableConstIterator.hpp"

class ITableIterator : public virtual ITableConstIterator {
public:
	virtual ~ITableIterator() {}

	virtual ITableIterator * getClone() const override = 0;

	virtual void insert(multi_base_types::table_row const &) = 0;	// inserts a row before current position
	virtual void update(multi_base_types::table_row const &) = 0;
	virtual void remove() = 0;
};

#endif
