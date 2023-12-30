#include <algorithm>
#include "SmartTableIterator.hpp"

SmartTableIterator::SmartTableIterator(ITableIterator * iter) : _iter(iter->getClone()) {}
SmartTableIterator::SmartTableIterator(SmartTableIterator const & other) : _iter(other._iter->getClone()) {}

SmartTableIterator & SmartTableIterator::operator=(SmartTableIterator const & other) {
	if (this != &other) {
		SmartTableIterator tmp(other);
		swap(tmp);
	}
	return *this;
}

SmartTableIterator::~SmartTableIterator() { delete _iter; }

void SmartTableIterator::swap(SmartTableIterator & other) { std::swap(_iter, other._iter); }

SmartTableIterator * SmartTableIterator::getClone() const { return new SmartTableIterator(*this); }

void SmartTableIterator::first() { _iter->first(); }
void SmartTableIterator::next() { _iter->next(); }
multi_base_types::table_row SmartTableIterator::get() const { return _iter->get(); }
bool SmartTableIterator::isEnd() const { return _iter->isEnd(); }

void SmartTableIterator::insert(multi_base_types::table_row const & row) { _iter->insert(row); }
void SmartTableIterator::update(multi_base_types::table_row const & row) { _iter->insert(row); }
void SmartTableIterator::remove() { _iter->remove(); }
