#ifndef BASE_TABLE_CONST_ITERATOR_HPP
#define BASE_TABLE_CONST_ITERATOR_HPP

#include <list>
#include "ITableConstIterator.hpp"

class BaseTable;

class BaseTableConstIterator : public virtual ITableConstIterator {
private:
	BaseTable const * _table;
	std::list<AutoValue *>::const_iterator _iter;

public:
	BaseTableConstIterator(BaseTable const * table);
	BaseTableConstIterator(BaseTable const & table);
	BaseTableConstIterator(BaseTableConstIterator const & other);
	BaseTableConstIterator & operator=(BaseTableConstIterator const & other);
	~BaseTableConstIterator() override;

	void swap(BaseTableConstIterator & other);

	BaseTableConstIterator * getClone() const override;

	void first() override;
	void next() override;
	multi_base_types::table_row get() const override;
	bool isEnd() const override;
};

#endif
