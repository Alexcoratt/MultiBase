#include <algorithm>

#include "BaseTableIterator.hpp"
#include "BaseTable.hpp"

BaseTableIterator::BaseTableIterator(BaseTable * table) : _table(table), _listIterator(table->_rows.begin()) {}

BaseTableIterator::BaseTableIterator(BaseTableIterator & other) : _table(other._table), _listIterator(other._listIterator) {}

BaseTableIterator & BaseTableIterator::operator=(BaseTableIterator & other) {
	if (this != &other) {
		BaseTableIterator tmp{other};
		swap(tmp);
	}
	return *this;
}

BaseTableIterator::~BaseTableIterator() {}

void BaseTableIterator::swap(BaseTableIterator & other) {
	std::swap(_table, other._table);
	std::swap(_listIterator, other._listIterator);
}

void BaseTableIterator::first() { _listIterator = _table->_rows.begin(); }
void BaseTableIterator::next() { ++_listIterator; }
std::map<std::string, AutoValue> BaseTableIterator::get() { return _table->getRow(_listIterator); }
bool BaseTableIterator::isEnd() { return _listIterator == _table->_rows.end(); }

void BaseTableIterator::insert(std::map<std::string, AutoValue> const & row) { _table->insertRow(row, _listIterator); }
void BaseTableIterator::update(std::map<std::string, AutoValue> const & row) { _table->updateRow(row, _listIterator); }
void BaseTableIterator::remove() { _table->removeRow(_listIterator); }
