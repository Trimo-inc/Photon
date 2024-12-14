#include "./SourceLocation.h"

diagnostic::SourceLocation::SourceLocation(const std::string_view& path, const size_t position = 0, const size_t line = 0)
: filepath(path), position(position), line(line) {}


std::string diagnostic::SourceLocation::to_string(void) const
{
    return (this->filepath + ':' + std::to_string(this->line) + ':' + std::to_string(this->position));
}

bool diagnostic::SourceLocation::operator==(const struct diagnostic::SourceLocation& other) const
{
    return (
    (other.filepath == this->filepath) && (other.position == this->position) && (other.line == this->line)
    );
}
