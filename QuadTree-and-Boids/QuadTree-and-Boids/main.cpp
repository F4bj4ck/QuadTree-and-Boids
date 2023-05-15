#include "Application.h"
#include <iostream>

int main()
{
    try
    {
        Application app;
        app.Run();
    }
    catch (...)
    {
        std::cout << "Something went wrong!\n";
    }
    
    return 0;
}