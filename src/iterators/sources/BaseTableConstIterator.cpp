#include <algorithm>

#include "BaseTableConstIterator.hpp"
#include "BaseTable.hpp"

#include "EndOfTableException.hpp"

BaseTableConstIterator::BaseTableConstIterator(BaseTable const * table) : _table(table), _iter(table->_rows.begin()) {}
BaseTableConstIterator::BaseTableConstIterator(BaseTable const & table) : BaseTableConstIterator(&table) {}
BaseTableConstIterator::BaseTableConstIterator(BaseTableConstIterator const & other) : _table(other._table), _iter(other._iter) {}

BaseTableConstIterator & BaseTableConstIterator::operator=(BaseTableConstIterator const & other) {
	if (this != &other) {
		BaseTableConstIterator tmp(other);
		swap(tmp);
	}
	return *this;
}

BaseTableConstIterator::~BaseTableConstIterator() {}

void BaseTableConstIterator::swap(BaseTableConstIterator & other) {
	std::swap(_table, other._table);
	std::swap(_iter, other._iter);
}

BaseTableConstIterator * BaseTableConstIterator::getClone() const { return new BaseTableConstIterator(*this); }

void BaseTableConstIterator::first() { _iter = _table->_rows.begin(); }
void BaseTableConstIterator::next() { ++_iter; }

multi_base_types::table_row BaseTableConstIterator::get() const {
	if (isEnd())
		throw EndOfTableException("BaseTable");
	return _table->getRow(_iter);
}

bool BaseTableConstIterator::isEnd() const { return _iter == _table->_rows.end(); }
