#ifndef BASE_TABLE_ITERATOR_HPP
#define BASE_TABLE_ITERATOR_HPP

#include <list>
#include <iterator>

#include "ITableIterator.hpp"

class BaseTableIterator : public ITableIterator {
private:
	std::list<AutoValue *> & _rows;
	std::_List_iterator<AutoValue *> _listIterator;

public:
	BaseTableIterator(std::list<AutoValue *> & rows);
	BaseTableIterator(BaseTableIterator & other);
	BaseTableIterator & operator=(BaseTableIterator & other);
	~BaseTableIterator() override;

	void swap(BaseTableIterator & other);

	void first() override;
	void next() override;
	std::map<std::string, AutoValue> get() override;
	bool isEnd() override;

	void insert(std::map<std::string, AutoValue> const & row) override;
	void update(std::map<std::string, AutoValue> const &) override;
	void remove() override;
};

#endif
