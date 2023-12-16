#ifndef CSV_TABLE_CONNECTION_ITERATOR_HPP
#define CSV_TABLE_CONNECTION_ITERATOR_HPP

#include <fstream>
#include <string>
#include <pthread.h>

#include "ITableIterator.hpp"

class CSVTableConnection;

class CSVTableConnectionIterator : public ITableIterator {
private:
	CSVTableConnection * _conn;
	std::fstream * _sourcestream;
	std::map<std::string, AutoValue> _currentRow;
	std::size_t _currentRowIndex;
	std::fstream::pos_type _lastPos;

public:
	CSVTableConnectionIterator(CSVTableConnection * conn);
	CSVTableConnectionIterator(CSVTableConnectionIterator const & other);
	CSVTableConnectionIterator & operator=(CSVTableConnectionIterator const & other);
	~CSVTableConnectionIterator() override;

	void swap(CSVTableConnectionIterator & other);

	void first() override;
	void next() override;
	std::map<std::string, AutoValue> get() const override;
	bool isEnd() const override;

	void insert(std::map<std::string, AutoValue> const &) override;
	void update(std::map<std::string, AutoValue> const &) override;
	void remove() override;
};

#endif
