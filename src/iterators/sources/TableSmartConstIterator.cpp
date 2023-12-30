#include <algorithm>
#include "TableSmartConstIterator.hpp"

TableSmartConstIterator::TableSmartConstIterator(ITableConstIterator const * iter) {
	auto smartConstIter = dynamic_cast<TableSmartConstIterator const *>(iter);
	if (smartConstIter)
		_constIter = smartConstIter->_constIter->getClone();
	else
		_constIter = iter->getClone();
}
TableSmartConstIterator::TableSmartConstIterator(ITableConstIterator const & iter) : TableSmartConstIterator(&iter) {}

TableSmartConstIterator::TableSmartConstIterator(TableSmartConstIterator const & other) : _constIter(other._constIter->getClone()) {}

TableSmartConstIterator & TableSmartConstIterator::operator=(TableSmartConstIterator const & other) {
	if (this != &other) {
		TableSmartConstIterator tmp(other);
		swap(tmp);
	}
	return *this;
}

TableSmartConstIterator::~TableSmartConstIterator() { delete _constIter; }

void TableSmartConstIterator::swap(TableSmartConstIterator & other) { std::swap(_constIter, other._constIter); }

TableSmartConstIterator * TableSmartConstIterator::getClone() const { return new TableSmartConstIterator(*this); }

void TableSmartConstIterator::first() { _constIter->first(); }
void TableSmartConstIterator::next() { _constIter->next(); }
multi_base_types::table_row TableSmartConstIterator::get() const { return _constIter->get(); }
bool TableSmartConstIterator::isEnd() const { return _constIter->isEnd(); }
