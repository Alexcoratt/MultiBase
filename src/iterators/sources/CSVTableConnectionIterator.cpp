#include <algorithm>
#include <stdexcept>

#include <iostream>

#include "CSVTableConnectionIterator.hpp"
#include "CSVTableConnection.hpp"

#include "EndOfTableException.hpp"

CSVTableConnectionIterator::CSVTableConnectionIterator(CSVTableConnection * conn) : _conn(conn), _sourcestream(new std::fstream(conn->_filename)) {
	auto headers = conn->getHeaders();
	CSVTableConnection::skipNextRows(*_sourcestream);
	_currentRow = CSVTableConnection::parseRow(_conn->getHeaders(), CSVTableConnection::readNextRow(*_sourcestream));
	++_currentRowIndex;
	_currentRowIndex = 0;
}

CSVTableConnectionIterator::CSVTableConnectionIterator(CSVTableConnectionIterator const & other) : _conn(other._conn), _sourcestream(new std::fstream(_conn->_filename)) {
	CSVTableConnection::skipNextRows(*_sourcestream, other._currentRowIndex + 1);
	next();
	_currentRowIndex = other._currentRowIndex;
}

CSVTableConnectionIterator & CSVTableConnectionIterator::operator=(CSVTableConnectionIterator const & other) {
	if (this != &other) {
		CSVTableConnectionIterator tmp(other);
		swap(tmp);
	}
	return *this;
}

CSVTableConnectionIterator::~CSVTableConnectionIterator() {
	delete _sourcestream;
}

void CSVTableConnectionIterator::swap(CSVTableConnectionIterator & other) {
	std::swap(_conn, other._conn);
	std::swap(_sourcestream, other._sourcestream);
	std::swap(_currentRow, other._currentRow);
	std::swap(_currentRowIndex, other._currentRowIndex);
}

void CSVTableConnectionIterator::first() {
	_sourcestream->clear();
	_sourcestream->seekg(0);
	_currentRowIndex = 0;
	next();
}

void CSVTableConnectionIterator::next() {
	if (isEnd())
		throw EndOfTableException(_conn->_filename);
	_currentRow = CSVTableConnection::parseRow(_conn->getHeaders(), CSVTableConnection::readNextRow(*_sourcestream));
	++_currentRowIndex;
}

std::map<std::string, AutoValue> CSVTableConnectionIterator::get() const { return _currentRow; }

bool CSVTableConnectionIterator::isEnd() const { return _currentRow.empty(); }
void CSVTableConnectionIterator::insert(std::map<std::string, AutoValue> const & row) { _conn->insertRow(row, _currentRowIndex++); }

void CSVTableConnectionIterator::update(std::map<std::string, AutoValue> const & row) {
	_currentRow = row;
	_conn->updateRow(row, _currentRowIndex);
}

void CSVTableConnectionIterator::remove() {
	next();
	_conn->removeRow(_currentRowIndex);
}
