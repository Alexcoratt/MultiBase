#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "BaseTable.hpp"

#include "BaseTableIterator.hpp"

BaseTable::BaseTable(std::vector<std::string> const & headings) {
	_width = headings.size();

	_headings = new std::string[_width];
	for (std::size_t i{0}; i < _width; ++i)
		_headings[i] = headings.at(i);
}

BaseTable::BaseTable(BaseTable const & other) : _width(other._width) {
	_headings = new std::string[_width];
	for (std::size_t i{0}; i < _width; ++i)
		_headings[i] = other._headings[i];

	for (auto row : other._rows) {
		auto newRow = new AutoValue[_width];
		for (std::size_t i{0}; i < _width; ++i)
			newRow[i] = row[i];
		_rows.push_back(newRow);
	}
}

BaseTable & BaseTable::operator=(BaseTable const & other) {
	if (this != &other) {
		BaseTable tmp(other);
		swap(tmp);
	}
	return *this;
}

BaseTable::~BaseTable() {
	delete[] _headings;
	for (AutoValue * row : _rows)
		delete[] row;
}

void BaseTable::swap(BaseTable & other) {
	std::swap(_width, other._width);
	std::swap(_headings, other._headings);
	std::swap(_rows, other._rows);
}

std::vector<std::string> BaseTable::getHeaders() const {
	std::vector<std::string> res(_width);
	for (std::size_t i{0}; i < _width; ++i)
		res[i] = _headings[i];
	return res;
}

std::size_t BaseTable::getWidth() const { return _width; }
std::size_t BaseTable::getHeight() const { return _rows.size(); }

template <typename KEY, typename VALUE>
std::map<KEY, VALUE> arrToMap(KEY const * keys, VALUE const * values, std::size_t const & count) {
	std::map<KEY, VALUE> res;
	for (std::size_t i = 0; i < count; ++i)
		res[keys[i]] = values[i];
	return res;
}

template <typename T>
std::_List_iterator<T> getNthIter(std::list<T> & list, std::size_t const & index) {
	std::size_t height = list.size();
	if (index >= height)
		throw std::out_of_range("BaseTable::getRow: index " + std::to_string(index) + " is out of height " + std::to_string(height));

	auto count = index;
	auto it = list.begin();
	while (count--)
		++it;
	return it;
}

template <typename T>
std::_List_const_iterator<T> getNthIter(std::list<T> const & list, std::size_t const & index) {
	std::size_t height = list.size();
	if (index >= height)
		throw std::out_of_range("BaseTable::getRow: index " + std::to_string(index) + " is out of height " + std::to_string(height));

	auto count = index;
	auto it = list.begin();
	while (count--)
		++it;
	return it;
}

std::map<std::string, AutoValue> BaseTable::getRow(std::size_t const & index) const {
	return arrToMap(_headings, *getNthIter(_rows, index), _width);
}

std::map<std::string, AutoValue> BaseTable::getRow(std::list<AutoValue *>::const_iterator const & iter) const {
	if (iter == _rows.end())
		throw std::out_of_range("BaseTable::getRow: iterator is out of range");
	return arrToMap(_headings, *iter, _width);
}

template <typename KEY, typename VALUE>
VALUE * mapToArr(VALUE * dest, KEY const * keys, std::size_t const & count, std::map<KEY, VALUE> const & map) {
	for (std::size_t i = 0; i < count; ++i) {
		try {
			dest[i] = map.at(keys[i]);
		} catch (std::out_of_range const & err) {
			std::cerr << err.what() << "\nmapToArr: no such key \"" << keys[i] << "\" in the map" << std::endl;
		}
	}
	return dest;
}

template <typename KEY, typename VALUE>
VALUE * mapToArr(KEY const * keys, std::size_t const & count, std::map<KEY, VALUE> const & map) {
	return mapToArr(new VALUE[count], keys, count, map);
}

void BaseTable::insertRow(std::map<std::string, AutoValue> const & row, const std::size_t & index) {
	auto iter = getNthIter(_rows, index);
	_rows.insert(iter, mapToArr(_headings, _width, row));
}

void BaseTable::insertRow(std::map<std::string, AutoValue> const & row, std::list<AutoValue *>::iterator & iter) {
	_rows.insert(iter, mapToArr(_headings, _width, row));
}

void BaseTable::appendRow(std::map<std::string, AutoValue> const & row) {
	_rows.push_back(mapToArr(_headings, _width, row));
}

void BaseTable::updateRow(std::map<std::string, AutoValue> const & row, std::size_t const & index) {
	mapToArr(*getNthIter(_rows, index), _headings, _width, row);
}

void BaseTable::updateRow(std::map<std::string, AutoValue> const & row, std::list<AutoValue *>::iterator & iter) {
	if (iter == _rows.end())
		throw std::out_of_range("BaseTable::updateRow: iterator is out of range");
	mapToArr(*iter, _headings, _width, row);
}

void BaseTable::removeRow(std::size_t const & index) {
	auto iter = getNthIter(_rows, index);
	delete [] *iter;
	_rows.erase(iter);
}

void BaseTable::removeRow(std::list<AutoValue *>::iterator & iter) {
	if (iter == _rows.end())
		throw std::out_of_range("BaseTable::removeRow: iterator is out of range");
	delete [] *iter;
	_rows.erase(iter);
}

multi_base_types::iterator BaseTable::getIterator() { return BaseTableIterator(this); }
multi_base_types::const_iterator BaseTable::getIterator() const { return BaseTableConstIterator(this); }
