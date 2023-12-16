#include <iostream>
#include <vector>

#include <ITable.hpp>
#include <BaseTable.hpp>
#include <CSVTableConnection.hpp>

#define FILENAME "../data/backloggd_games_short.csv"

std::vector<std::map<std::string, AutoValue>> const people = {
	{
		{"id", 0},
		{"first name", "Alexander"},
		{"last name", "Smirnov"}
	},
	{
		{"id", 1},
		{"first name", "Ilya"},
		{"last name", "Koltsov"}
	},
	{
		{"id", 2},
		{"first name", "Shakh"},
		{"last name", "Isakov"}
	}
};

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

	ITable * table = new CSVTableConnection(filename);//new BaseTable({ "id", "first name", "last name" });

	//for (auto row : people)
	//	iter->insert(row);

	auto const headings = table->getHeaders();
	ITableIterator * iter = table->getIterator();
	unsigned int count = 0;
	while (count++ != 15) {
		for (auto const & heading : headings)
			std::cout << heading << ": " << iter->get().at(heading) << '\n';
		std::cout << std::endl;
		iter->next();
	}
	CSVTableConnectionIterator iter2(*dynamic_cast<CSVTableConnectionIterator *>(iter));
	while (!iter2.isEnd()) {
		for (auto const & heading : headings)
			std::cout << heading << ": " << iter2.get().at(heading) << '\n';
		std::cout << std::endl;
		iter2.next();
	}
	delete iter;
	delete table;

	return 0;
}
