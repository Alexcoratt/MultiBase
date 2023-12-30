#include <algorithm>
#include "TableSmartIterator.hpp"

TableSmartIterator::TableSmartIterator(ITableIterator const * iter) : TableSmartConstIterator(iter) {
	auto smartIter = dynamic_cast<TableSmartIterator const *>(iter);
	if (smartIter)
		_iter = smartIter->_iter->getClone();
	else
		_iter = iter->getClone();
}

TableSmartIterator::TableSmartIterator(ITableIterator const & other) : TableSmartIterator(&other) {}

TableSmartIterator::TableSmartIterator(TableSmartIterator const & other) : TableSmartConstIterator(other), _iter(other._iter->getClone()) {}

TableSmartIterator & TableSmartIterator::operator=(TableSmartIterator const & other) {
	if (this != &other) {
		TableSmartIterator tmp(other);
		swap(tmp);
	}
	return *this;
}

TableSmartIterator::~TableSmartIterator() { delete _iter; }

void TableSmartIterator::swap(TableSmartIterator & other) {
	TableSmartConstIterator::swap(other);
	std::swap(_iter, other._iter);
}

TableSmartIterator * TableSmartIterator::getClone() const { return new TableSmartIterator(*this); }

void TableSmartIterator::first() {
	TableSmartConstIterator::first();
	_iter->first();
}

void TableSmartIterator::next() {
	TableSmartConstIterator::next();
	_iter->next();
}

void TableSmartIterator::insert(multi_base_types::table_row const & row) { _iter->insert(row); }
void TableSmartIterator::update(multi_base_types::table_row const & row) { _iter->insert(row); }
void TableSmartIterator::remove() { _iter->remove(); }
