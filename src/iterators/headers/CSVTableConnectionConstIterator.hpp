#ifndef CSV_TABLE_CONNECTION_CONST_ITERATOR_HPP
#define CSV_TABLE_CONNECTION_CONST_ITERATOR_HPP

#include <fstream>
#include "ITableConstIterator.hpp"

class CSVTableConnection;

class CSVTableConnectionConstIterator : public virtual ITableConstIterator {
protected:
	CSVTableConnection const * _conn;
	std::ifstream * _sourcestream;
	multi_base_types::table_row _currentRow;
	std::size_t _currentRowIndex;
	std::ifstream::pos_type _lastPos;

public:
	CSVTableConnectionConstIterator(CSVTableConnection const * conn);
	CSVTableConnectionConstIterator(CSVTableConnection const & conn);
	CSVTableConnectionConstIterator(CSVTableConnectionConstIterator const & other);
	CSVTableConnectionConstIterator & operator=(CSVTableConnectionConstIterator const & other);
	~CSVTableConnectionConstIterator() override;

	void swap(CSVTableConnectionConstIterator & other);

	CSVTableConnectionConstIterator * getClone() const override;

	void first() override;
	void next() override;
	multi_base_types::table_row get() const override;
	bool isEnd() const override;
};

#endif
