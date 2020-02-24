#include <iostream>
#include <exception>
#include "InputHandler.h"
#include "Writer.h"

using Text = std::string;
using int32 = int;

InputHandler IH;

void ClearScreen();
void PrintExplanation();
Text GetComponentName();
bool AskForNew();

int main ()
{
    bool isNew = false;
    do {
        try {
            PrintExplanation();
            Text cmp = GetComponentName();
            Writer W(cmp);
            W.CreateDirs();
            isNew = AskForNew();
        }
        catch (std::exception& e) {
            return 0;
        }
    } while(isNew);

    return 0;
}

void ClearScreen() {
    #ifdef WINDOWS
        system("cls");
    #else
        system("clear");
    #endif
}

void PrintExplanation() {
    ClearScreen();
    std::cout << "React component generator" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "This program will generate a react component for you based on the name you provide." << std::endl;
    std::cout << "The component name shouldn't start with capital letter and you shouldn't use its plural form!" << std::endl;
    std::cout << "The reason is that the name will be converted by default so for example, if you pass 'page'" << std::endl;
    std::cout << "as a component name, it will be output as Pages, PagesController, PagesView, PageModel, PageDAO, etc..." << std::endl;
}

Text GetComponentName() {
    Text component = "";
    
    EInputStatus Status = EInputStatus::EMPTY_STRING;
    do
    {
        std::cout << std::endl << "Provide a valid component name or enter q to quit:" << std::endl;
        std::getline(std::cin, component);
        if (component == "q") throw std::invalid_argument("q");
        Status = IH.Validate(component);
        switch (Status)
        {
        case EInputStatus::EMPTY_STRING:
            std::cout << "Empty string isn't allowed.";
            break;
        case EInputStatus::ENDS_WITH_S:
            std::cout << "The component shouldn't end with 's' character.";
            break;
        case EInputStatus::TOO_LONG:
            std::cout << "The maximum component length is 10 characters!";
            break;
        default:
            break;
        }
    } while (Status != EInputStatus::OK);
    return IH.Convert(component);
}

bool AskForNew () {
    Text answer = "n";
    std::cout << "Do you want to create another component? (y/n - defaults to no)" << std::endl;
    std::getline(std::cin, answer);
    if (answer == "y") return true;

    return false;
}