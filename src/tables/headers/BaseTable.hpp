#ifndef BASE_TABLE_HPP
#define BASE_TABLE_HPP

#include <list>

#include "ITable.hpp"

class BaseTable : public ITable {
friend class BaseTableIterator;

private:
	std::size_t _width;
	std::string * _headings;
	std::list<AutoValue *> _rows;

	multi_base_types::table_row getRow(std::list<AutoValue *>::iterator const &) const;
	void insertRow(multi_base_types::table_row const &, std::list<AutoValue *>::iterator &);
	void updateRow(const multi_base_types::table_row &row, std::list<AutoValue *>::iterator &);
	void removeRow(std::list<AutoValue *>::iterator &);

public:
	BaseTable(std::vector<std::string> const & headings);
	BaseTable(BaseTable const & other);
	BaseTable & operator=(BaseTable const &);
	~BaseTable();

	void swap(BaseTable & other);

	std::vector<std::string> getHeaders() const override;
	std::size_t getWidth() const override;
	std::size_t getHeight() const override;

	multi_base_types::table_row getRow(const std::size_t &index) const override;

	void insertRow(const multi_base_types::table_row &row, const std::size_t &index = 0) override;

	void appendRow(const multi_base_types::table_row &row) override;
	void updateRow(const multi_base_types::table_row &row, const std::size_t &index) override;
	void removeRow(const std::size_t &index) override;

	multi_base_types::iterator getIterator() override;
};

#endif
