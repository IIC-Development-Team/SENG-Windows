#include "Exception.h"

SENG::SengException::SengException(std::source_location loc)
    : loc(loc)
{}

const char* SENG::SengException::what() const noexcept
{
    std::ostringstream oss;
    oss << "Exception caught!\n"
        << "File: " << loc.file_name() << "\n"
        << "Line: " << loc.line() << "\n"
        << "Func: " << loc.function_name() << "\n";

    wBuffer = oss.str();
    return wBuffer.c_str();
}
