#ifndef I_TABLE_HPP
#define I_TABLE_HPP

#include "table_types.hpp"

class ITable {
public:
	virtual ~ITable() {}

	virtual std::vector<std::string> getHeaders() const = 0;
	virtual std::size_t getWidth() const = 0;
	virtual std::size_t getHeight() const = 0;

	virtual multi_base_types::table_row getRow(std::size_t const & index) const = 0;
	virtual void insertRow(multi_base_types::table_row const & row, std::size_t const & index = 0) = 0;
	virtual void appendRow(multi_base_types::table_row const & row) = 0;
	virtual void updateRow(multi_base_types::table_row const & row, std::size_t const & index) = 0;
	virtual void removeRow(std::size_t const & index) = 0;

	// returns a pointer to a new ITableIterator
	// so a client has to delete it manually
	virtual multi_base_types::iterator getIterator() = 0;
	virtual multi_base_types::const_iterator getIterator() const = 0;
};

#include "TableSmartConstIterator.hpp"
#include "TableSmartIterator.hpp"

#endif
