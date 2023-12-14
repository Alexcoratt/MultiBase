#include <algorithm>
#include <stdexcept>

#include "CSVTableConnectionIterator.hpp"
#include "CSVTableConnection.hpp"

#include "EndOfTableException.hpp"

CSVTableConnectionIterator::CSVTableConnectionIterator(CSVTableConnection * conn) : _conn(conn), _file(new std::fstream(conn->_filename)) {
	_currentRowIndex = 0;
	next();
}

CSVTableConnectionIterator::CSVTableConnectionIterator(CSVTableConnectionIterator const & other) : _conn(other._conn), _file(new std::fstream(_conn->_filename)) {
	CSVTableConnection::skipNextRows(*_file, other._currentRowIndex);
	next();
}

CSVTableConnectionIterator & CSVTableConnectionIterator::operator=(CSVTableConnectionIterator const & other) {
	if (this != &other) {
		CSVTableConnectionIterator tmp(other);
		swap(tmp);
	}
	return *this;
}

CSVTableConnectionIterator::~CSVTableConnectionIterator() {
	_file->close();
	delete _file;
}

void CSVTableConnectionIterator::swap(CSVTableConnectionIterator & other) {
	std::swap(_conn, other._conn);
	std::swap(_file, other._file);
	std::swap(_currentRow, other._currentRow);
	std::swap(_currentRowIndex, other._currentRowIndex);
}

void CSVTableConnectionIterator::first() {
	_file->clear();
	_file->seekg(0);
	_currentRowIndex = 0;
	next();
}

void CSVTableConnectionIterator::next() {
	if (isEnd())
		throw EndOfTableException(_conn->_filename);
	_currentRow = CSVTableConnection::parseRow(_conn->getHeaders(), CSVTableConnection::readNextRow(*_file));
	++_currentRowIndex;
}

std::map<std::string, AutoValue> CSVTableConnectionIterator::get() const { return _currentRow; }

bool CSVTableConnectionIterator::isEnd() const { return _file->eof(); }
void CSVTableConnectionIterator::insert(std::map<std::string, AutoValue> const & row) { _conn->insertRow(row, _currentRowIndex++); }

void CSVTableConnectionIterator::update(std::map<std::string, AutoValue> const & row) {
	_currentRow = row;
	_conn->updateRow(row, _currentRowIndex);
}

void CSVTableConnectionIterator::remove() {
	next();
	_conn->removeRow(_currentRowIndex);
}
