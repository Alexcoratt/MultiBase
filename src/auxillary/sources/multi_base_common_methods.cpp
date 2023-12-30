#include "TableException.hpp"
#include "multi_base_common_methods.hpp"

void table_methods::copyTable(ITable const * source, ITable * dest) {
	auto headers = source->getHeaders();
	if (headers != dest->getHeaders())
		throw TableException("Tables have different headers");

	auto destIter = dest->getIterator();
	for (auto sourceIter = source->getIterator(); !sourceIter.isEnd(); sourceIter.next()) {
		if (destIter.isEnd())
			destIter.insert(sourceIter.get());
		else {
			destIter.update(sourceIter.get());
			destIter.next();
		}
	}
}

void table_methods::printTable(ITable const * table, std::ostream & out) {
	auto headers = table->getHeaders();
	for (auto iter = table->getIterator(); !iter.isEnd(); iter.next()) {
		auto row = iter.get();

		for (auto const & header : headers)
			out << header << ":\t" << row.at(header) << '\n';
		out << std::endl;
	}
}
