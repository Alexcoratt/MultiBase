#ifndef BASE_TABLE_ITERATOR_HPP
#define BASE_TABLE_ITERATOR_HPP

#include <list>
#include <iterator>

#include <AutoValue.hpp>

#include "ITableIterator.hpp"

class BaseTableIterator;

#include "BaseTable.hpp"

class BaseTableIterator : public ITableIterator {
private:
	BaseTable * _table;
	std::_List_iterator<AutoValue *> _listIterator;

public:
	BaseTableIterator(BaseTable * table);
	BaseTableIterator(BaseTableIterator const & other);
	BaseTableIterator & operator=(BaseTableIterator const & other);
	~BaseTableIterator() override;

	void swap(BaseTableIterator & other);

	void first() override;
	void next() override;
	std::map<std::string, AutoValue> get() override;
	bool isEnd() override;

	virtual void insertAfter(std::map<std::string, AutoValue> const & row) override;
};

#endif
