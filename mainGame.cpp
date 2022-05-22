#include "header.h"
#include "elebeastClass.h"

int main( )
{
    int menuOption = 0;

    cout << "Welcome to the realm of Elebeasts!" << endl << endl;
    while (menuOption != 1 && menuOption != 2)
    {
        cout << "Enter 1 to start a new game or enter 2 to load your file: ";
        cin >> menuOption;
        if (menuOption != 1 && menuOption != 2)
            cout << "That's not a valid option!" << endl << endl;
    }


}