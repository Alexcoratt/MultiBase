#ifndef I_FLAG_HPP
#define I_FLAG_HPP

#include <string>
#include <AutoValue.hpp>

class IFlag {
public:
	virtual AutoValue getValueToWrite(AutoValue const &) = 0;
	virtual float getPriority() const = 0;
	virtual std::string getName() const = 0;
};

#endif
