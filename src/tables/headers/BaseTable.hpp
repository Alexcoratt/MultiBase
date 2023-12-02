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

public:
	BaseTable(std::vector<std::string> const & headings);
	BaseTable(BaseTable const & other);
	BaseTable & operator=(BaseTable const &);
	~BaseTable();

	std::vector<std::string> getHeadings() const override;
	std::size_t getWidth() const override;
	std::size_t getHeight() const override;

	std::map<std::string, AutoValue> getRow(const std::size_t &index) const override;
	void insertRow(const std::map<std::string, AutoValue> &row, const std::size_t &index = 0) override;
	void appendRow(const std::map<std::string, AutoValue> &row) override;
	void updateRow(const std::map<std::string, AutoValue> &row, const std::size_t &index) override;
	void removeRow(const std::size_t &index) override;

	std::shared_ptr<ITableIterator> getIterator() override;
};

#include "BaseTableIterator.hpp"

#endif
