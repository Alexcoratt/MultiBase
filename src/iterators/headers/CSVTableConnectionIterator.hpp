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
	multi_base_types::table_row _currentRow;
	std::size_t _currentRowIndex;
	std::fstream::pos_type _lastPos;

public:
	CSVTableConnectionIterator(CSVTableConnection * conn);
	CSVTableConnectionIterator(CSVTableConnectionIterator const & other);
	CSVTableConnectionIterator & operator=(CSVTableConnectionIterator const & other);
	~CSVTableConnectionIterator() override;

	void swap(CSVTableConnectionIterator & other);

	CSVTableConnectionIterator * getClone() const override;

	void first() override;
	void next() override;
	multi_base_types::table_row get() const override;
	bool isEnd() const override;

	void insert(multi_base_types::table_row const &) override;
	void update(multi_base_types::table_row const &) override;
	void remove() override;
};

#endif
