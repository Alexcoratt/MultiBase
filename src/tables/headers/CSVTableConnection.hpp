#ifndef CSV_TABLE_CONNECTION_HPP
#define CSV_TABLE_CONNECTION_HPP

#include <string>

#include "ITable.hpp"
#include "ILineParser.hpp"
#include "CSVTableConnectionIterator.hpp"

class CSVTableConnection : public ITable {
friend class CSVTableConnectionIterator;

private:
	std::string _filename;
	ILineParser * _lineParser;

	static std::string readNextRow(std::istream & input);
	static void skipNextRows(std::istream & input, std::size_t rowCount = 1);

public:
	CSVTableConnection(std::string const & filename, ILineParser * _lineParser);
	CSVTableConnection(CSVTableConnection const & other);
	CSVTableConnection & operator=(CSVTableConnection const & other);
	~CSVTableConnection() override;

	void swap(CSVTableConnection & other);

	std::vector<std::string> getHeaders() const override;
	std::size_t getWidth() const override;
	std::size_t getHeight() const override;

	std::map<std::string, AutoValue> getRow(std::size_t const & index) const override;
	void insertRow(std::map<std::string, AutoValue> const & row, std::size_t const & index = 0) override;
	void appendRow(std::map<std::string, AutoValue> const & row) override;
	void updateRow(std::map<std::string, AutoValue> const & row, std::size_t const & index) override;
	void removeRow(std::size_t const & index) override;

	CSVTableConnectionIterator * getIterator() override;
};

#endif
