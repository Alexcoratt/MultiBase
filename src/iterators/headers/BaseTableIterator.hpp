#ifndef BASE_TABLE_ITERATOR_HPP
#define BASE_TABLE_ITERATOR_HPP

#include <list>
#include <iterator>

#include "ITableIterator.hpp"

class BaseTable;

class BaseTableIterator : public ITableIterator {
private:
	BaseTable * _table;
	std::list<AutoValue *>::iterator _listIterator;

public:
	BaseTableIterator(BaseTable * table);
	BaseTableIterator(BaseTableIterator & other);
	BaseTableIterator & operator=(BaseTableIterator & other);
	~BaseTableIterator() override;

	void swap(BaseTableIterator & other);

	void first() override;
	void next() override;
	std::map<std::string, AutoValue> get() override;
	bool isEnd() override;

	void insert(std::map<std::string, AutoValue> const &) override;
	void update(std::map<std::string, AutoValue> const &) override;
	void remove() override;
};

#endif
