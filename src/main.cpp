#include "PasswordManager.h"

int main()
{
    PasswordManager pd;
    int k = 0; 
    bool flag = true;

    while(flag)
    {
        system("clear");
        pd.printTitle();
        std::cout << "1. Generate password." << std::endl;
        std::cout << "2. Show all passwords." << std::endl;
        std::cout << "3. Exit. " << std::endl;
        std::cin >> k;
        switch(k)
        {
            case 1:
                system("clear");
                pd.printTitle();
                pd.createPasswordLog();
                break;
            case 2:
                system("clear");
                pd.printTitle();
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