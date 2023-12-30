#include <algorithm>
#include <stdexcept>

#include <iostream>

#include "BaseTable.hpp"

#include "CSVTableConnectionIterator.hpp"
#include "CSVTableConnection.hpp"

CSVTableConnectionIterator::CSVTableConnectionIterator(CSVTableConnection * conn) : CSVTableConnectionConstIterator(conn), _conn(conn), _sourcestream(new std::fstream(conn->_filename)) { first(); }

CSVTableConnectionIterator::CSVTableConnectionIterator(CSVTableConnection & conn) : CSVTableConnectionIterator(&conn) {}

CSVTableConnectionIterator::CSVTableConnectionIterator(CSVTableConnectionIterator const & other) : CSVTableConnectionConstIterator(other), _conn(other._conn), _sourcestream(new std::fstream(other._conn->_filename)) {
	_sourcestream->seekg(other._sourcestream->tellg());
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
	CSVTableConnectionConstIterator::swap(other);
	std::swap(_conn, other._conn);
	std::swap(_sourcestream, other._sourcestream);
}

CSVTableConnectionIterator * CSVTableConnectionIterator::getClone() const { return new CSVTableConnectionIterator(*this); }

void CSVTableConnectionIterator::first() {
	CSVTableConnectionConstIterator::first();
	_sourcestream->clear();
	_sourcestream->seekg(0);
	CSVTableConnection::skipNextRows(*_sourcestream);
}

void CSVTableConnectionIterator::next() {
	CSVTableConnectionConstIterator::next();
	_sourcestream->seekg(_lastPos);
}

void CSVTableConnectionIterator::insert(multi_base_types::table_row const & row) {
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

	std::fstream writer(_conn->_filename);
	writer.seekg(_lastPos);
	writer << _conn->_lineParser->parseReverse(headers, row) << std::endl;
	_sourcestream->seekg(writer.tellg());
	for (auto btIter = bt->getIterator(); !btIter.isEnd(); btIter.next()) {
		writer << _conn->_lineParser->parseReverse(headers, btIter.get()) << std::endl;
	}
	delete bt;
	next();
}

void CSVTableConnectionIterator::update(multi_base_types::table_row const & row) {
	_currentRow = row;
	_conn->updateRow(row, _currentRowIndex);
}

void CSVTableConnectionIterator::remove() {
	next();
	_conn->removeRow(_currentRowIndex);
}
