#ifndef BASE_TABLE_HPP
#define BASE_TABLE_HPP

#include <list>

#include "ITable.hpp"
#include "BaseTableIterator.hpp"

class BaseTable : public ITable {
friend class BaseTableIterator;

private:
	std::size_t _width;
	std::string * _headings;
	std::list<AutoValue *> _rows;

	std::map<std::string, AutoValue> getRow(std::list<AutoValue *>::iterator const &) const;
	void insertRow(std::map<std::string, AutoValue> const &, std::list<AutoValue *>::iterator &);
	void updateRow(const std::map<std::string, AutoValue> &row, std::list<AutoValue *>::iterator &);
	void removeRow(std::list<AutoValue *>::iterator &);

public:
	BaseTable(std::vector<std::string> const & headings);
	BaseTable(BaseTable const & other);
	BaseTable & operator=(BaseTable const &);
	~BaseTable();

	void swap(BaseTable & other);

	std::vector<std::string> getHeadings() const override;
	std::size_t getWidth() const override;
	std::size_t getHeight() const override;

	std::map<std::string, AutoValue> getRow(const std::size_t &index) const override;

	void insertRow(const std::map<std::string, AutoValue> &row, const std::size_t &index = 0) override;

	void appendRow(const std::map<std::string, AutoValue> &row) override;
	void updateRow(const std::map<std::string, AutoValue> &row, const std::size_t &index) override;
	void removeRow(const std::size_t &index) override;

	BaseTableIterator * getIterator() override;
};

#endif
