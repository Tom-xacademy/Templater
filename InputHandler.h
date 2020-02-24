#include <string>
#include <stdio.h>

using Text = std::string;

enum class EInputStatus
{
	OK,
	EMPTY_STRING,
	ENDS_WITH_S,
	TOO_LONG
};

class InputHandler {
    public:
	EInputStatus Validate(Text word) const;
    Text Convert(Text word) const;
	private:
	Text component;
};