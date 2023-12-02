#include <algorithm>

#include "BaseTable.hpp"

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

std::vector<std::string> BaseTable::getHeadings() const {
	std::vector<std::string> res(_width);
	for (std::size_t i{0}; i < _width; ++i)
		res[i] = _headings[i];
	return res;
}

std::size_t BaseTable::getWidth() const { return _width; }
std::size_t BaseTable::getHeight() const { return _rows.size(); }

std::map<std::string, AutoValue> BaseTable::getRow(std::size_t const & index) const {
	auto count = index;
	auto it = _rows.begin();
	while (count && it != _rows.end())
		++it;

	std::map<std::string, AutoValue> res;
	for (std::size_t i{0}; i < _width; ++i)
		res[_headings[i]] = (*it)[i];

	return res;
}

void BaseTable::insertRow(std::map<std::string, AutoValue> )


