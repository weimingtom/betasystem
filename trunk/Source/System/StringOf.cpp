#include "System/StringOf.hpp"

#include <sstream>

std::string StringOf( int num )
{
	std::ostringstream string_stream;
    string_stream << num ;
    return string_stream.str();
}

