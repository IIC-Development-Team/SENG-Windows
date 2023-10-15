#pragma once
#include "Core.h"

namespace SENG
{
	class SENG_API SengException : public std::exception
	{
	public:
		SengException(std::source_location loc = std::source_location::current());
		const char* what() const noexcept override;

	protected:
		std::source_location loc;
		mutable std::string wBuffer;
	};
}