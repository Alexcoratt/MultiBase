#ifndef TABLE_SMART_CONST_ITERATOR_HPP
#define TABLE_SMART_CONST_ITERATOR_HPP

#include "ITableConstIterator.hpp"

class TableSmartConstIterator : public virtual ITableConstIterator {
private:
	ITableConstIterator * _constIter;

public:
	explicit TableSmartConstIterator(ITableConstIterator const * iterator);
	TableSmartConstIterator(ITableConstIterator const & iterator);
	TableSmartConstIterator(TableSmartConstIterator const & other);
	TableSmartConstIterator & operator=(TableSmartConstIterator const & other);
	~TableSmartConstIterator() override;

	void swap(TableSmartConstIterator & other);

	TableSmartConstIterator * getClone() const override;

	void first() override;
	void next() override;
	multi_base_types::table_row get() const override;
	bool isEnd() const override;
};

#endif
