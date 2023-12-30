#ifndef TABLE_SMART_ITERATOR_HPP
#define TABLE_SMART_ITERATOR_HPP

#include "TableSmartConstIterator.hpp"
#include "ITableIterator.hpp"

class TableSmartIterator : public TableSmartConstIterator, public ITableIterator {
private:
	ITableIterator * _iter;

public:
	explicit TableSmartIterator(ITableIterator const * iterator);
	TableSmartIterator(ITableIterator const & iterator);
	TableSmartIterator(TableSmartIterator const & other);
	TableSmartIterator & operator=(TableSmartIterator const & other);
	~TableSmartIterator();

	void swap(TableSmartIterator & other);

	TableSmartIterator * getClone() const override;

	void first() override;
	void next() override;

	void insert(multi_base_types::table_row const &) override;
	void update(multi_base_types::table_row const &) override;
	void remove() override;
};

#endif
