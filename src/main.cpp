#include <iostream>
#include <vector>

#include <ITable.hpp>
#include <BaseTable.hpp>
#include <CSVTableConnection.hpp>

#define FILENAME "../data/testdata/backloggd_games_short.csv"

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

	CSVTableConnection csvTable(filename);
	BaseTable baseTable(csvTable.getHeaders());
	auto csvIter = csvTable.getIterator();
	//auto btIter = baseTable.getIterator();
	while(!csvIter->isEnd()) {
		//btIter->insert(csvIter->get());
		csvIter->next();
	}

	delete csvIter;
	//delete btIter;

	return 0;
}
