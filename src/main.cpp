#include <iostream>
#include <vector>

#include <ITable.hpp>
#include <BaseTable.hpp>

constexpr char const * endAsString(bool end) {
	if (end)
		return "end";
	return "not end";
}

template <typename KEY, typename VALUE>
constexpr void printMap(std::map<KEY, VALUE> const & map) {
	for (auto it = map.begin(); it != map.end(); ++it)
		std::cout << it->first << '\t' << it->second << '\n';
	std::cout << std::endl;
}

template <typename T>
constexpr void printRow(std::vector<T> const & row) {
	for (T const & value : row)
		std::cout << value << '\t';
	std::cout << std::endl;
}

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

void printTable(ITable * table) {
	auto headings = table->getHeaders();
	printRow(headings);

	auto iter = table->getIterator();
	while (!iter->isEnd()) {
		auto row = iter->get();
		for (auto const & heading : headings)
			std::cout << row.at(heading) << '\t';
		std::cout << std::endl;

		iter->next();
	}
	delete iter;
	std::cout << std::endl;
}

int main(int argc, char ** argv) {
	ITable * table = new BaseTable({ "id", "first name", "last name" });
	ITableIterator * iter = table->getIterator();

	std::cout << endAsString(iter->isEnd()) << std::endl;

	for (auto row : people)
		iter->insert(row);

	std::cout << endAsString(iter->isEnd()) << std::endl;

	printTable(table);

	table->removeRow(1);
	printTable(table);

	auto tmpIter = table->getIterator();
	tmpIter->next();
	tmpIter->remove();
	delete tmpIter;
	printTable(table);

	table->updateRow(people.at(1), 0);
	printTable(table);

	table->appendRow(people.at(2));
	printTable(table);

	delete iter;

	return 0;
}
