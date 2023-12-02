#ifndef BASE_TABLE_ITERATOR_HPP
#define BASE_TABLE_ITERATOR_HPP

#include <list>
#include <iterator>

#include "ITableIterator.hpp"

template <typename T>
class BaseTableIterator : public ITableIterator {
private:
	std::list<T> & _rows;
	std::_List_iterator<T> _listIterator;

public:
	BaseTableIterator(std::list<T> & rows);
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
