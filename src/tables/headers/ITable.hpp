#ifndef I_TABLE_HPP
#define I_TABLE_HPP

#include <map>
#include <string>
#include <vector>
#include <memory>

#include <AutoValue.hpp>
#include <ITableIterator.hpp>

class ITable {
public:
	virtual std::vector<std::string> getHeadings() const = 0;
	virtual std::size_t getWidth() const = 0;
	virtual std::size_t getHeight() const = 0;

	virtual std::map<std::string, AutoValue> getRow(std::size_t const & index) const = 0;
	virtual void insertRow(std::map<std::string, AutoValue> const & row, std::size_t const & index = 0) = 0;
	virtual void appendRow(std::map<std::string, AutoValue> const & row);
	virtual void updateRow(std::map<std::string, AutoValue> const & row, std::size_t const & index) = 0;
	virtual void removeRow(std::size_t const & index) = 0;

	virtual std::shared_ptr<ITableIterator> getIterator() = 0;
};

#endif
