#include <algorithm>
#include <stdexcept>

#include <iostream>

#include "BaseTable.hpp"

#include "CSVTableConnectionIterator.hpp"
#include "CSVTableConnection.hpp"

#include "EndOfTableException.hpp"

CSVTableConnectionIterator::CSVTableConnectionIterator(CSVTableConnection * conn) : _conn(conn), _sourcestream(new std::fstream(conn->_filename)) { first(); }

CSVTableConnectionIterator::CSVTableConnectionIterator(CSVTableConnectionIterator const & other) : _conn(other._conn), _sourcestream(new std::fstream(_conn->_filename)) {
	_sourcestream->seekg(other._sourcestream->tellg());
	_currentRow = other._currentRow;
	_currentRowIndex = other._currentRowIndex;
	_lastPos = other._lastPos;
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
	CSVTableConnection::skipNextRows(*_sourcestream);
	auto lp = _sourcestream->tellg();
	_currentRow = _conn->_lineParser->parseLine(_conn->getHeaders(), CSVTableConnection::readNextRow(*_sourcestream));
	_currentRowIndex = 0;
	_lastPos = lp;
}

void CSVTableConnectionIterator::next() {
	if (isEnd())
		throw EndOfTableException(_conn->_filename);
	auto lp = _sourcestream->tellg();
	_currentRow = _conn->_lineParser->parseLine(_conn->getHeaders(), CSVTableConnection::readNextRow(*_sourcestream));
	++_currentRowIndex;
	_lastPos = lp;
}

std::map<std::string, AutoValue> CSVTableConnectionIterator::get() const { return _currentRow; }

bool CSVTableConnectionIterator::isEnd() const { return _currentRow.empty(); }

void CSVTableConnectionIterator::insert(std::map<std::string, AutoValue> const & row) {
	auto headers = _conn->getHeaders();
	if (isEnd()) {
		std::ofstream writer(_conn->_filename, std::ios::app);
		writer << _conn->_lineParser->parseReverse(headers, row) << std::endl;
		auto lp = _sourcestream->tellg();
		_sourcestream->seekg(writer.tellp());
		_lastPos = lp;
		++_currentRowIndex;
		return;
	}

	BaseTable * bt = new BaseTable{headers};
	auto iterCopy{*this};
	while (!iterCopy.isEnd()) {
		bt->appendRow(iterCopy.get());
		iterCopy.next();
	}

	auto btIter = bt->getIterator();

	std::fstream writer(_conn->_filename);
	writer.seekg(_lastPos);
	writer << _conn->_lineParser->parseReverse(headers, row) << std::endl;
	_sourcestream->seekg(writer.tellg());
	while (!btIter->isEnd()) {
		writer << _conn->_lineParser->parseReverse(headers, btIter->get()) << std::endl;
		btIter->next();
	}
	delete btIter;
	delete bt;
	next();
}

void CSVTableConnectionIterator::update(std::map<std::string, AutoValue> const & row) {
	_currentRow = row;
	_conn->updateRow(row, _currentRowIndex);
}

void CSVTableConnectionIterator::remove() {
	next();
	_conn->removeRow(_currentRowIndex);
}
