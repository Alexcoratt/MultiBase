#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <set>

#include <ITable.hpp>
#include <BaseTable.hpp>
#include <CSVTableConnection.hpp>
#include <TableException.hpp>

#include <NullValue.hpp>
#include <VectorValue.hpp>
#include <StringValue.hpp>
#include <DateValue.hpp>

#include <BaseLineParser.hpp>
#include <BaseValueParser.hpp>

#include <split_string.h>
#include <auxillary_classes.hpp>

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

void insertVectorValue(std::set<StringValue> & dest, AutoValue const & source) {
	std::size_t len = source.size();
	for (std::size_t i = 0; i < len; ++i) {
		if (!source.at(i).isString())
			std::cout << source << '\n' << source.at(i) << std::endl;
		dest.insert(source.at(i).toString());
	}
}

bool contains(AutoValue const & container, AutoValue const & search) {
	auto len = container.size();
	for (std::size_t i = 0; i < len; ++i) {
		//std::cout << container.getTypeName() << ' ' << search.getTypeName() << std::endl;
		if (container.at(i) == search)
			return true;
	}
	return false;
}

void countGamesOfTheDeveloper(ITable * games, std::string const devName) {
	auto iter = games->getIterator();
	unsigned int gameCount = 0;
	while (!iter->isEnd()) {
		auto row = iter->get();
		if (contains(row.at("Developers"), devName))
			++gameCount;
		iter->next();
	}
	delete iter;
	std::cout << "Developer \"" << devName << "\" created " << gameCount << " game(s)" << std::endl;
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

	MyValueParser valueParser;
	BaseLineParser lineParser{&valueParser};
	MyLineParser myLineParser;
	CSVTableConnection csvTable(filename, &myLineParser);
	auto const headers = csvTable.getHeaders();

	BaseTable baseTable(headers);

	BaseTable devs({"id", "name"});
	std::set<StringValue> devNames;

	BaseTable genres({"id", "name"});
	std::set<StringValue> genreNames;

	BaseTable platforms({"id", "name"});
	std::set<StringValue> platformNames;

	auto csvIter = csvTable.getIterator();
	while(!csvIter->isEnd()) {
		auto row = csvIter->get();
		baseTable.appendRow(row);

		insertVectorValue(devNames, row.at("Developers"));
		//std::cout << row.at("Developers") << std::endl;

		insertVectorValue(platformNames, row.at("Platforms"));
		//std::cout << row.at("Platforms") << std::endl;

		insertVectorValue(genreNames, row.at("Genres"));
		//std::cout << row.at("Genres") << std::endl;

		csvIter->next();
	}
	delete csvIter;

	printTable(&baseTable);

	std::size_t count = 0;
	for (auto const & name : devNames)
		devs.appendRow({
			{"id", count++},
			{"name", name}
		});

	count = 0;
	for (auto const & name : platformNames)
		platforms.appendRow({
			{"id", count++},
			{"name", name}
		});

	count = 0;
	for (auto const & name : genreNames)
		genres.appendRow({
			{"id", count++},
			{"name", name}
		});

	std::cout << "Developers count: " << devs.getHeight() << std::endl;
	std::cout << "Platforms count: " << platforms.getHeight() << std::endl;
	std::cout << "Genres count: " << genres.getHeight() << std::endl;

	countGamesOfTheDeveloper(&baseTable, "ZA/UM");
	countGamesOfTheDeveloper(&baseTable, "Electronic Arts");
	countGamesOfTheDeveloper(&baseTable, "Respawn Entertainment");

	return 0;
}
