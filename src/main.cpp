#include <iostream>
#include <vector>

#include <ITable.hpp>
#include <BaseTable.hpp>
#include <CSVTableConnection.hpp>

#include <BaseLineParser.hpp>
#include <BaseValueParser.hpp>

#define FILENAME "../data/testdata/backloggd_games_short.csv"

void printTable(ITable * table) {
	auto iter = table->getIterator();
	auto headers = table->getHeaders();
	while (!iter->isEnd()) {
		auto row = iter->get();
		for (auto const & header : headers)
			std::cout << header << ": " << row.at(header) << '\n';
		std::cout << std::endl;
		iter->next();
	}
	delete iter;
}

int main(int argc, char ** argv) {
	if (argc > 2) {
		printf("Usage: %s [filename]\n", argv[0]);
		return -1;
	}

	char const defaultFilename[] = FILENAME;
	char const * filename;
	if (argc == 2)
		filename = argv[1];
	else
		filename = defaultFilename;

	BaseValueParser bvp;
	BaseLineParser blp{&bvp};
	CSVTableConnection csvTable(filename, &blp);
	auto const headers = csvTable.getHeaders();
	BaseTable baseTable(headers);
	auto csvIter = csvTable.getIterator();
	while(!csvIter->isEnd()) {
		baseTable.appendRow(csvIter->get());
		csvIter->next();
	}
	delete csvIter;

	printTable(&baseTable);

	return 0;
}
