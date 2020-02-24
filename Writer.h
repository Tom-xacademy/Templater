#include <string>
#include <stdlib.h>

using Text = std::string;

struct CNames {
    Text CMPS = "";
    Text CMP = "";
    Text CVS = "";
    Text CV = "";
};

class Writer {
    public:
    Writer(Text component);

    void CreateDirs(void) const;

    private:
    void CloneFiles( Text root ) const;
    Text GetCurrentWorkingDir( void ) const;
    Text Capitalize(Text word, bool is_plural) const;
    void ReplaceText(Text& parsed_text) const;
    CNames names;
};