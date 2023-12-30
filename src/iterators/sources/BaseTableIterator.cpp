#include <algorithm>

#include "BaseTableIterator.hpp"
#include "BaseTable.hpp"

#include "EndOfTableException.hpp"

BaseTableIterator::BaseTableIterator(BaseTable * table) : BaseTableConstIterator(table), _table(table), _iter(table->_rows.begin()) {}

BaseTableIterator::BaseTableIterator(BaseTable & table) : BaseTableIterator(&table) {}

BaseTableIterator::BaseTableIterator(BaseTableIterator const & other) : BaseTableConstIterator(other._table), _table(other._table), _iter(other._iter) {}

BaseTableIterator & BaseTableIterator::operator=(BaseTableIterator const & other) {
	if (this != &other) {
		BaseTableIterator tmp{other};
		swap(tmp);
	}
	return *this;
}

BaseTableIterator::~BaseTableIterator() {}

void BaseTableIterator::swap(BaseTableIterator & other) {
	BaseTableConstIterator::swap(other);
	std::swap(_table, other._table);
	std::swap(_iter, other._iter);
}

BaseTableIterator * BaseTableIterator::getClone() const { return new BaseTableIterator(*this); }

void BaseTableIterator::first() {
	BaseTableConstIterator::first();
	_iter = _table->_rows.begin();
}

void BaseTableIterator::next() {
	BaseTableConstIterator::next();
	++_iter;
}

void BaseTableIterator::insert(multi_base_types::table_row const & row) { _table->insertRow(row, _iter); }
void BaseTableIterator::update(multi_base_types::table_row const & row) {
	if (isEnd())
		throw EndOfTableException("BaseTable");
	_table->updateRow(row, _iter);
}
void BaseTableIterator::remove() { _table->removeRow(_iter); }
