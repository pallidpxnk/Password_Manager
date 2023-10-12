#include "PasswordManager.h"

void printTitle()
{
    std::cout << "⌜⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⌝" << std::endl;
    std::cout << "|                      Password Manager                        |" << std::endl;
    std::cout << "⌞₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋⌟" << std::endl;
}

int main()
{
    PasswordManager pd;
    int k = 0; 
    bool flag = true;

    while(flag)
    {
        system("clear");
        printTitle();
        std::cout << "1. Generate password." << std::endl;
        std::cout << "2. Show all passwords." << std::endl;
        std::cout << "3. Exit. " << std::endl;
        std::cin >> k;
        switch(k)
        {
            case 1:
                system("clear");
                printTitle();
                pd.createPasswordLog();
                break;
            case 2:
                system("clear");
                printTitle();
                pd.showAllPasswords();
                break;
            case 3:
                flag = false;
                exit(0);
                break;
        }
    }
        
    return 0;
}