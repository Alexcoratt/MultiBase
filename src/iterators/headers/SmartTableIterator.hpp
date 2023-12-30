#ifndef SMART_TABLE_ITERATOR_HPP
#define SMART_TABLE_ITERATOR_HPP

#include "ITableIterator.hpp"

class SmartTableIterator : public ITableIterator {
private:
	ITableIterator * _iter;

public:
	SmartTableIterator(ITableIterator * iterator);
	SmartTableIterator(SmartTableIterator const & other);
	SmartTableIterator & operator=(SmartTableIterator const & other);
	~SmartTableIterator();

	void swap(SmartTableIterator & other);

	SmartTableIterator * getClone() const override;

	void first() override;
	void next() override;
	multi_base_types::table_row get() const override;
	bool isEnd() const override;

	void insert(multi_base_types::table_row const &) override;
	void update(multi_base_types::table_row const &) override;
	void remove() override;
};

#endif
