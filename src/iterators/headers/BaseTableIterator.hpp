#ifndef BASE_TABLE_ITERATOR_HPP
#define BASE_TABLE_ITERATOR_HPP

#include <list>
#include <iterator>

#include "ITableIterator.hpp"
#include "BaseTableConstIterator.hpp"

class BaseTable;

class BaseTableIterator : public BaseTableConstIterator, public ITableIterator {
private:
	BaseTable * _table;
	std::list<AutoValue *>::iterator _iter;

public:
	BaseTableIterator(BaseTable * table);
	BaseTableIterator(BaseTable & table);
	BaseTableIterator(BaseTableIterator const & other);
	BaseTableIterator & operator=(BaseTableIterator const & other);
	~BaseTableIterator() override;

	void swap(BaseTableIterator & other);

	BaseTableIterator * getClone() const override;

	void first() override;
	void next() override;

	void insert(multi_base_types::table_row const &) override;
	void update(multi_base_types::table_row const &) override;
	void remove() override;
};

#endif
