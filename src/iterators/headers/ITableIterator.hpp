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
	virtual std::map<std::string, AutoValue> get() { return ((ITableIterator const *)this)->get(); }
	virtual std::map<std::string, AutoValue> get() const = 0;
	virtual bool isEnd() const = 0;

	// inserts a row before current position
	virtual void insert(std::map<std::string, AutoValue> const &) = 0;
	virtual void update(std::map<std::string, AutoValue> const &) = 0;
	virtual void remove() = 0;
};

#endif
