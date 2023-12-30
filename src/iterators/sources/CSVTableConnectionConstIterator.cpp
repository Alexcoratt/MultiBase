#include <algorithm>

#include "CSVTableConnectionConstIterator.hpp"
#include "CSVTableConnection.hpp"

#include "EndOfTableException.hpp"

CSVTableConnectionConstIterator::CSVTableConnectionConstIterator(CSVTableConnection const * conn) : _conn(conn), _sourcestream(new std::ifstream(conn->_filename)) { first(); }

CSVTableConnectionConstIterator::CSVTableConnectionConstIterator(CSVTableConnection const & conn) : CSVTableConnectionConstIterator(&conn) {}

CSVTableConnectionConstIterator::CSVTableConnectionConstIterator(CSVTableConnectionConstIterator const & other) : _conn(other._conn), _sourcestream(new std::ifstream(other._conn->_filename)) {
	_sourcestream->seekg(other._sourcestream->tellg());
	_currentRow = other._currentRow;
	_currentRowIndex = other._currentRowIndex;
	_lastPos = other._lastPos;
}

CSVTableConnectionConstIterator & CSVTableConnectionConstIterator::operator=(CSVTableConnectionConstIterator const & other) {
	if (this != &other) {
		CSVTableConnectionConstIterator tmp(other);
		swap(tmp);
	}
	return *this;
}

CSVTableConnectionConstIterator::~CSVTableConnectionConstIterator() {
	delete _sourcestream;
}

void CSVTableConnectionConstIterator::swap(CSVTableConnectionConstIterator & other) {
	std::swap(_conn, other._conn);
	std::swap(_sourcestream, other._sourcestream);
	std::swap(_currentRow, other._currentRow);
	std::swap(_currentRowIndex, other._currentRowIndex);
}

CSVTableConnectionConstIterator * CSVTableConnectionConstIterator::getClone() const { return new CSVTableConnectionConstIterator(*this); }

void CSVTableConnectionConstIterator::first() {
	_sourcestream->clear();
	_sourcestream->seekg(0);
	CSVTableConnection::skipNextRows(*_sourcestream);
	auto lp = _sourcestream->tellg();
	_currentRow = _conn->_lineParser->parseLine(_conn->getHeaders(), CSVTableConnection::readNextRow(*_sourcestream));
	_currentRowIndex = 0;
	_lastPos = lp;
}

void CSVTableConnectionConstIterator::next() {
	if (isEnd())
		throw EndOfTableException(_conn->_filename);
	auto lp = _sourcestream->tellg();
	_currentRow = _conn->_lineParser->parseLine(_conn->getHeaders(), CSVTableConnection::readNextRow(*_sourcestream));
	++_currentRowIndex;
	_lastPos = lp;
}

multi_base_types::table_row CSVTableConnectionConstIterator::get() const { return _currentRow; }

bool CSVTableConnectionConstIterator::isEnd() const { return _currentRow.empty(); }
