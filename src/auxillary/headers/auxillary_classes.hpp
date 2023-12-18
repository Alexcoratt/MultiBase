#ifndef AUXILLARY_CLASSES_HPP
#define AUXILLARY_CLASSES_HPP

#include <cstring>
#include <iostream>
#include <sstream>

#include "IValueParser.hpp"
#include "ILineParser.hpp"
#include "split_string.h"
#include "TableException.hpp"

#include <VectorValue.hpp>
#include <AutoValue.hpp>
#include <NullValue.hpp>
#include <DateValue.hpp>

class MyValueParser : public IValueParser {
public:
	AutoValue parseVectorString(std::string const & str) const {
		unsigned int width;
		char ** parts;
		split_string_screened(str.c_str(), ',', '\'', &width, &parts);
		VectorValue res;
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

	inline static constexpr char const * months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	DateValue parseDate(std::string const & str) const {
		std::stringstream sstr{str};
		char monthName[4];
		char day[2];
		char year[5];
		sstr.ignore(1);
		sstr >> monthName;
		sstr.ignore(1);
		sstr >> day;
		sstr.ignore(2);
		sstr >> year;
		std::cout << day << ' ' << monthName << ' ' << year << std::endl;
		return 0;
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
		if (value.at(0) == '\"')
			return parseQuotedString(value);
		if (value.at(0) == '\'')
			return value.substr(1, value.size() - 2);
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

class MyLineParser : public ILineParser {
public:
	AutoValue parseVector(std::string str) const {
		unsigned int width;
		char ** parts;
		if (str.at(0) == '\"')
			str = str.substr(1, str.size() - 2);
		if (str.at(0) == '[')
			str = str.substr(1, str.size() - 2);
		split_string_screened(str.c_str(), ',', '\'', &width, &parts);
		VectorValue res;
		for (unsigned int i = 0; i < width; ++i) {
			if (strlen(parts[i]) == 0) {
				res.push_back(NullValue{});
				continue;
			}
			int delta = parts[i][0] == ' ';
			res.push_back(parseQuotedString(parts[i] + delta));
			free(parts[i]);
		}
		free(parts);
		return res;
	}

	AutoValue parseQuotedString(std::string const & str) const {
		if (str.size() < 3)
			return NullValue{};
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
		if (str == "N/A")
			return NullValue{};
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

	inline static constexpr char const * months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	static char getMonthNumber(char const * monthName) {
		for (char i = 0; i < 12; ++i)
			if (strcmp(monthName, months[i]) == 0)
				return i + 1;
		return 13;
	}

	DateValue parseDate(std::string const & str) const {
		if (str == "TBD")
			return 0;
		unsigned int count;
		char ** parts;
		split_string(str.c_str(), ' ', &count, &parts);
		parts[1][2] = '\0';
		parts[2][4] = '\0';
		int month = getMonthNumber(parts[0] + 1);
		if (month == 13)
			return 0;
		int day = std::stoi(parts[1]);
		unsigned int year = std::stoul(parts[2]);

		DateValue res;
		res.set(day, month, year);

		for (unsigned int i = 0; i < count; ++i)
			free(parts[i]);
		free(parts);
		return res;
	}

	std::map<std::string, AutoValue> parseLine(std::vector<std::string> const & headers, std::string const & line) const override {
		unsigned int width;
		char ** parts;
		split_string_screened(line.c_str(), ',', '\"', &width, &parts);

		if (width == 0) {
			for (unsigned int i = 0; i < width; ++i)
				free(parts[i]);
			free(parts);
			return {};
		}

		unsigned int headerCount = headers.size();
		if (width != headerCount && width != 0)
			throw TableException("headers array and row elements array have different sizes: " + std::to_string(headerCount) + " required and " + std::to_string(width) + " provided");

		std::map<std::string, AutoValue> res;
		res[headers[0]] = parseDigital(parts[0]);
		res[headers[1]] = parseString(parts[1]);
		res[headers[2]] = parseDate(parts[2]);
		res[headers[3]] = parseVector(parts[3]);
		res[headers[4]] = parseQuotedString(parts[4]);
		res[headers[5]] = parseVector(parts[5]);
		res[headers[6]] = parseVector(parts[6]);
		res[headers[7]] = parseDigital(parts[7]);
		res[headers[8]] = parseDigital(parts[8]);
		res[headers[9]] = parseDigital(parts[9]);
		res[headers[10]] = parseDigital(parts[10]);
		res[headers[11]] = parseDigital(parts[11]);
		res[headers[12]] = parseDigital(parts[12]);
		res[headers[13]] = parseDigital(parts[13]);

		for (unsigned int i = 0; i < width; ++i)
			free(parts[i]);
		free(parts);
		return res;
	}

	std::string parseReverse(std::vector<std::string> const & headers, std::map<std::string, AutoValue> const & row) const override {
		std::stringstream res;
		res << row.at(headers.at(0));
		unsigned int width = headers.size();
		for (unsigned int i = 1; i < width; ++i)
			res << ',' << row.at(headers.at(i));
		return res.str();
	}
};

#endif
