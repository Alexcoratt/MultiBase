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
	BaseTable table({ "id", "first name", "last name" });
	ITableIterator * iter = table.getIterator();

	std::cout << endAsString(iter->isEnd()) << std::endl;

	for (auto row : people)
		iter->insert(row);

	std::cout << endAsString(iter->isEnd()) << std::endl;
	iter->first();

	while (!iter->isEnd()) {
		printMap(iter->get());
		iter->next();
	}

	return 0;
}
