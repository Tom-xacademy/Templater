#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include "Writer.h"
#include <experimental/filesystem>
#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/ 

#ifdef WINDOWS
    #include <direct.h>
    #include <windows.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #include <limits.h>
    #define GetCurrentDir getcwd
#endif

using Text = std::string;
namespace fs = std::experimental::filesystem;

Text GetExeDir() {

    //TODO make this work on windows as well
    //This solution is for linux only. <3
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    std::string f_path = std::string( result, (count > 0) ? count : 0 );
    //19 is the lenght of /dist/Templater.exe
    //I know this is a bullshit solution but it works for me since this
    //is just for personal use and the name won't be modified.
    return f_path.substr(0, f_path.length() - 18);
}

Writer::Writer(Text component) {
    names.CMPS = Capitalize(component, true);
    names.CMP = Capitalize(component, false);
    names.CVS = component + "s";
    names.CV = component;
}

Text Writer::GetCurrentWorkingDir( void ) const {
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    Text current_working_dir(buff);
    return current_working_dir;
}

Text Writer::Capitalize(Text word, bool is_plural) const {
    word[0] = toupper(word[0]);

    if (is_plural) return word + "s";

    return word;
}

void Writer::CreateDirs( void ) const {
    Text path = GetCurrentWorkingDir();
    Text root = path + "/" + names.CMPS;
    fs::create_directory(root);
    fs::create_directory(root + "/Controller");
    fs::create_directory(root + "/View");
    fs::create_directory(root + "/Static");
    fs::create_directory(root + "/Interfaces");
    fs::create_directory(root + "/Model");
    fs::create_directory(root + "/DAO");
    std::cout << std::endl << "Created directories..." << std::endl;
    CloneFiles(root);
}

Text ReadFile(Text path) {
    std::ifstream t(path);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    Text buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size);
    return buffer;
}

void Repl(Text& str, const Text& from, const Text& to) {
    if(from.empty()) return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != Text::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

void Writer::ReplaceText(Text& parsed_text) const {
    Repl(parsed_text, "CMPS", names.CMPS);
    Repl(parsed_text, "CMP", names.CMP);
    Repl(parsed_text, "CVS", names.CVS);
    Repl(parsed_text, "CV", names.CV);
}

void WriteFile(Text filepath, Text text_value) {
    std::ofstream outfile (filepath, std::ios::out);
    outfile << text_value << std::endl;
    outfile.close();
}

void Writer::CloneFiles( Text root ) const {
    
    // Controller methods
    Text p = GetExeDir() + "/Templates/Template.controller.tsx";
    
    Text CtrlPath = GetExeDir() + "/Templates/Template.controller.tsx";
    std::cout << "path from is " << CtrlPath << std::endl;
    std::cout << "path to is " << root + "/Controller/" + names.CMPS + ".controller.tsx" << std::endl;
    Text Ctrl = ReadFile(CtrlPath);
    std::cout << std::endl << "Finished reading Controller..." << std::endl;
    ReplaceText(Ctrl);
    WriteFile(root + "/Controller/" + names.CMPS + ".controller.tsx", Ctrl);
    std::cout << std::endl << "Replaced Controller text..." << std::endl;

    // View methods

    Text View = ReadFile(GetExeDir() + "/Templates/Template.view.tsx");
    std::cout << std::endl << "Finished reading View..." << std::endl;
    ReplaceText(View);
    WriteFile(root + "/View/" + names.CMPS + ".view.tsx", View);
    std::cout << std::endl << "Replaced View text..." << std::endl;

    // ElementView methods

    Text ElementView = ReadFile(GetExeDir() + "/Templates/TemplateElement.view.tsx");
    std::cout << std::endl << "Finished reading ElementView..." << std::endl;
    ReplaceText(ElementView);
    WriteFile(root + "/View/" + names.CMP + "Element.view.tsx", ElementView);
    std::cout << std::endl << "Replaced ElementView text..." << std::endl;

    // Static methods

    Text Stat = ReadFile(GetExeDir() + "/Templates/Template.form.ts");
    std::cout << std::endl << "Finished reading Stat..." << std::endl;
    ReplaceText(Stat);
    WriteFile(root + "/Static/" + names.CMP + ".form.ts", Stat);
    std::cout << std::endl << "Replaced Stat text..." << std::endl;

    // Interfaces methods

    Text Interfaces = ReadFile(GetExeDir() + "/Templates/ITemplateForm.interface.ts");
    std::cout << std::endl << "Finished reading Interfaces..." << std::endl;
    ReplaceText(Interfaces);
    WriteFile(root + "/Interfaces/I" + names.CMP + "Form.interface.ts", Interfaces);
    std::cout << std::endl << "Replaced Interfaces text..." << std::endl;

    // Model methods

    Text Model = ReadFile(GetExeDir() + "/Templates/Template.model.ts");
    std::cout << std::endl << "Finished reading Model..." << std::endl;
    ReplaceText(Model);
    WriteFile(root + "/Model/" + names.CMP + ".model.ts", Model);
    std::cout << std::endl << "Replaced Model text..." << std::endl;

    // DAO methods

    Text Dao = ReadFile(GetExeDir() + "/Templates/Template.dao.ts");
    std::cout << std::endl << "Finished reading Dao..." << std::endl;
    ReplaceText(Dao);
    WriteFile(root + "/DAO/" + names.CMP + ".dao.ts", Dao);
    std::cout << std::endl << "Replaced Dao text..." << std::endl;

    // Finished process
    std::cout << std::endl << "Finished writing files." << std::endl;
}