#ifndef CSV_TABLE_CONNECTION_ITERATOR_HPP
#define CSV_TABLE_CONNECTION_ITERATOR_HPP

#include <fstream>
#include <string>
#include <pthread.h>

#include "CSVTableConnectionConstIterator.hpp"
#include "ITableIterator.hpp"

class CSVTableConnectionIterator : public CSVTableConnectionConstIterator, public ITableIterator {
private:
	CSVTableConnection * _conn;
	std::fstream * _sourcestream;

public:
	CSVTableConnectionIterator(CSVTableConnection * conn);
	CSVTableConnectionIterator(CSVTableConnection & conn);
	CSVTableConnectionIterator(CSVTableConnectionIterator const & other);
	CSVTableConnectionIterator & operator=(CSVTableConnectionIterator const & other);
	~CSVTableConnectionIterator() override;

	void swap(CSVTableConnectionIterator & other);

	CSVTableConnectionIterator * getClone() const override;

	void first() override;
	void next() override;

	void insert(multi_base_types::table_row const &) override;
	void update(multi_base_types::table_row const &) override;
	void remove() override;
};

#endif
