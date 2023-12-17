#include <iostream>
#include <vector>
#include <cstring>

#include <ITable.hpp>
#include <BaseTable.hpp>
#include <CSVTableConnection.hpp>

#include <NullValue.hpp>

#include <BaseLineParser.hpp>
#include <BaseValueParser.hpp>

#include <split_string.h>

#include <set>

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

class MyValueParser : public IValueParser {
public:
	AutoValue parseVectorString(std::string const & str) const {
		unsigned int width;
		char ** parts;
		split_string_screened(str.c_str(), ',', '\'', &width, &parts);
		AutoValue res;
		for (unsigned int i = 0; i < width; ++i) {
			if (strlen(parts[i]) == 0) {
				res.push_back(NullValue{});
				continue;
			}
			char delta = 0;
			if (parts[i][0] == ' ')
				delta = 1;
			if (strlen(parts[i]) > delta)
				res.push_back(parseValue(std::string(parts[i] + delta)));
			else
				res.push_back(parseValue(std::string(parts[i])));
			free(parts[i]);
		}
		free(parts);
		return res;
	}

	AutoValue parseQuotedString(std::string const & str) const {
		if (str.at(1) == '[')
			return parseVectorString(str.substr(2, str.size() - 4));
		std::size_t len = str.size() - 2;
		char buffer[len + 1];
		std::memset(buffer, '\0', len + 1);
		std::size_t delta = 0;
		for (std::size_t i = 0; i + delta < len; ++i) {
			if (str.at(i + delta + 1) == '\"' && str.at(i + delta + 2) == '\"')
				++delta;
			buffer[i] = str.at(i + delta + 1);
		}
		return buffer;
	}

	AutoValue parseString(std::string const & str) const {
		return str;
	}

	AutoValue parseDigital(std::string const & str) const {
		if (str.find('.') == std::string::npos) {
			try {
				if (str.back() == 'K')
					return std::stoul(str.substr(0, str.size() - 1)) * 1000;
				return std::stoul(str);
			} catch (std::exception const & err) {
				std::cerr << "Invalid value: \"" << str << '\"' << std::endl;
				throw err;
			}
		}
		if (str.back() == 'K')
			return std::stod(str.substr(0, str.size() - 1)) * 1000;
		return std::stod(str);
	}

	static bool isDigital(std::string const & str) {
		if (str.empty())
			return false;

		std::size_t len = str.size() - 1;
		if (len == 0)
			return std::isdigit(str.at(0));

		unsigned int pointCount = 0;
		for (std::size_t i = 0; i < len; ++i) {
			if (str.at(i) == '.')
				if (++pointCount != 1)
					return false;
			if (!std::isdigit(str.at(i)) && str.at(i) != '.')
				return false;
		}
		return true;
	}

	AutoValue parseValue(std::string const & value) const override {
		if (value.empty() || value == "N/A")
			return NullValue{};
		if (value.at(0) == '\'' || value.at(0) == '\"')
			return parseQuotedString(value);
		if (value.at(0) == '[')
			return parseVectorString(value.substr(1, value.size() - 2));
		if (isDigital(value))
			return parseDigital(value);
		return parseString(value);
	}

	std::string parseReverse(AutoValue const & value) const override {
		return (std::string)value;
	}
};

void insertVectorValue(std::set<AutoValue> & dest, AutoValue const & source) {
	std::size_t len = source.size();
	for (std::size_t i = 0; i < len; ++i) {
		dest.insert(source.at(i));
	}
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
	CSVTableConnection csvTable(filename, &lineParser);
	auto const headers = csvTable.getHeaders();

	BaseTable baseTable(headers);

	BaseTable devs({"id", "name"});
	std::set<AutoValue> devNames;

	BaseTable genres({"id", "name"});
	std::set<AutoValue> genreNames;

	BaseTable platforms({"id", "name"});
	std::set<AutoValue> platformNames;

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

	return 0;
}
