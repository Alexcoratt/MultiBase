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
	BaseTableIterator(BaseTableIterator const & other);
	BaseTableIterator & operator=(BaseTableIterator const & other);
	~BaseTableIterator() override;

	void swap(BaseTableIterator & other);

	void first() override;
	void next() override;
	std::map<std::string, AutoValue> get() const override;
	bool isEnd() const override;

	void insert(std::map<std::string, AutoValue> const &) override;
	void update(std::map<std::string, AutoValue> const &) override;
	void remove() override;
};

#endif
