#include <algorithm>

#include "BaseTableIterator.hpp"

BaseTableIterator::BaseTableIterator(std::list<AutoValue *> & rows) : _rows(rows), _listIterator(rows.begin()) {}

BaseTableIterator::BaseTableIterator(BaseTableIterator & other) : _rows(other._rows), _listIterator(other._listIterator) {}

BaseTableIterator & BaseTableIterator::operator=(BaseTableIterator & other) {
	if (this != &other) {
		BaseTableIterator tmp{other};
		swap(tmp);
	}
	return *this;
}

BaseTableIterator::~BaseTableIterator() {}

void BaseTableIterator::swap(BaseTableIterator & other) {
	std::swap(_rows, other._rows);
	std::swap(_listIterator, other._listIterator);
}

void BaseTableIterator::first() { _listIterator = _rows.begin(); }
void BaseTableIterator::next() { ++_listIterator; }
std::map<std::string, AutoValue> BaseTableIterator::get() {

}
