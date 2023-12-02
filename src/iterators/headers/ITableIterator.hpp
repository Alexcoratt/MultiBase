#ifndef I_TABLE_ITERATOR_HPP
#define I_TABLE_ITERATOR_HPP

#include <map>
#include <string>

#include <AutoValue.hpp>

class ITableIterator {
public:
	virtual ~ITableIterator() {}

	virtual void first() = 0;
	virtual void next() = 0;
	virtual std::map<std::string, AutoValue> get() = 0;
	virtual bool isEnd() = 0;

	virtual void insertAfter(std::map<std::string, AutoValue> const &) = 0;
	virtual void set(std::map<std::string, AutoValue> const &) = 0;
	virtual void remove() = 0;
};

#endif
