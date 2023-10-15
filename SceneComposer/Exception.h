#pragma once
#include <exception>
#include <source_location>
#include <string>
#include <sstream>

class Exception : public std::exception
{
public:
	Exception(std::source_location loc = std::source_location::current());
	const char* what() const noexcept override;

protected:
	std::source_location loc;
	mutable std::string wBuffer;
};
