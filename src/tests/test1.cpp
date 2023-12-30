#include <iostream>

#include <CSVTableConnection.hpp>
#include <BaseTable.hpp>

#include <BaseValueParser.hpp>
#include <BaseLineParser.hpp>

#include <multi_base_common_methods.hpp>

int main(int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return -1;
	}

	BaseValueParser valueParser;
	BaseLineParser lineParser(&valueParser);
	CSVTableConnection conn(argv[1], &lineParser);
	BaseTable table(conn.getHeaders());

	table_methods::copyTable(&conn, &table);
	table_methods::printTable(&table);

	return 0;
}
