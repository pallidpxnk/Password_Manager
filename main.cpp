#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <iomanip>

class PasswordManager
{
public:

    std::string generateStrongPassword() {
        const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
        const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const std::string numbers = "0123456789";
        const std::string specialChars = "!@#$%^&*()_+-=[]{}|;:,.<>?";

        const std::string remainingChars = lowercase + uppercase + numbers + specialChars;

        srand(time(0));

        std::string password;
        password.push_back(uppercase[rand() % uppercase.length()]);
        password.push_back(numbers[rand() % numbers.length()]);
        password.push_back(specialChars[rand() % specialChars.length()]);
        password.push_back(uppercase[rand() % uppercase.length()]);
        password.push_back(numbers[rand() % numbers.length()]);
        password.push_back(specialChars[rand() % specialChars.length()]);

        int remainingLength = 24;

        for (int i = 0; i < remainingLength; ++i) {
            password.push_back(remainingChars[rand() % remainingChars.length()]);
        }

        std::random_shuffle(password.begin(), password.end());

        return password;
    }

    void createPasswordLog()
    {

        std::string inputLogin;
        std::string inputSiteName;
        std::cout << "\nEnter site: ";
        std::cin >> inputSiteName;

        if (!std::cin) {
            std::cerr << "Error reading input for site name. Aborting." << std::endl;
            return;
        }

        std::cout << "\nEnter login: ";
        std::cin >> inputLogin;

        if (!std::cin) {
            std::cerr << "Error reading input for site name. Aborting." << std::endl;
            return;
        }

        setLogin(inputLogin);
        setSiteName(inputSiteName);
        std::string inputPassword = generateStrongPassword();
        setPassword(inputPassword);

        std::string path = "passwords.txt";
        std::fstream fs;
        fs.open(path, std::fstream::out | std::fstream::app);

        if (!fs.is_open()) {
            std::cerr << "Error opening file " << path << ". Aborting." << std::endl;
            return;
        }
        
        std::cout << std::endl << "Site: " << getSiteName() << std::endl << "Login: " << getLogin() << std::endl << "Password: " << getPassword() << std::endl;
        
        std::string answer;
        while (true) {
            std::cout << std::endl << "Edit or Continue? (e/c) ";
            std::cin >> answer;

            if (answer == "e") {
                editPasswordEntry();
                break;
            } else if (answer == "c") {
                break;
            } else {
                std::cout << "Invalid input. Please enter 'e' to edit or 'c' to continue." << std::endl;
            }
        }

        fs << std::endl << "Site: " << getSiteName() << std::endl << "Login: " << getLogin() << std::endl << "Password: " << getPassword() << std::endl;
        fs.close();
    }

    void editPasswordEntry() 
    {
        std::string inputLogin;
        std::string inputSiteName;
        std::cout << "\nEnter site: ";
        std::cin >> inputSiteName;

        if (!std::cin) {
            std::cerr << "Error reading input for site name. Aborting." << std::endl;
            return;
        }

        std::cout << "\nEnter login: ";
        std::cin >> inputLogin;

        if (!std::cin) {
            std::cerr << "Error reading input for site name. Aborting." << std::endl;
            return;
        }
        
        setLogin(inputLogin);
        setSiteName(inputSiteName);
        std::string inputPassword = generateStrongPassword();
        setPassword(inputPassword);

        std::cout << std::endl << "Site: " << getSiteName() << std::endl << "Login: " << getLogin() << std::endl << "Password: " << getPassword() << std::endl;

        std::string answer;
        while (true) {
            std::cout << std::endl << "Edit or Continue? (e/c) ";
            std::cin >> answer;

            if (answer == "e") {
                editPasswordEntry();
                break;
            } else if (answer == "c") {
                break;
            } else {
                std::cout << "Invalid input. Please enter 'e' to edit or 'c' to continue." << std::endl;
            }
        }
    }

    void showAllPasswords() {
        std::string path = "passwords.txt";
        std::ifstream file(path);

        if (!file.is_open()) {
            std::cerr << "Error opening file " << path << ". Aborting." << std::endl;
            return;
        }

        std::string line;

        std::cout << std::endl;
        std::cout << std::left << std::setw(20) << "Site" << std::setw(20) << "Login" << std::setw(20) << "Password" << std::endl;
        std::cout << std::string(60, '-') << std::endl;

        while (std::getline(file, line)) {
            if (line.find("Site: ") != std::string::npos) {
                std::string siteName = line.substr(6);
                std::string login, password;

                if (std::getline(file, login) && std::getline(file, password)) {
                    login = login.substr(7);
                    password = password.substr(10);

                    std::cout << std::left << std::setw(20) << siteName << std::setw(20) << login << std::setw(20) << password << std::endl;
                }
            }
        }

        std::string answer;
        while (true) {
            std::cout << std::endl << "Continue? (y/n) ";
            std::cin >> answer;

            if (answer == "y") {
                break;
            } else if (answer == "n") {
                exit(0);
                break;
            } else {
                std::cout << "Invalid input. Please enter 'e' to edit or 'c' to continue." << std::endl;
            }
        }
        file.close();
    }

    void setSiteName(std::string str)
    {
        this->siteName = str;
    }
    std::string getSiteName()
    {
        return this->siteName;
    }

    void setPassword(std::string str)
    {
        this->password = str;
    }
    std::string getPassword()
    {
        return this->password;
    }

    void setLogin(std::string str)
    {
        this->login = str;
    }
    std::string getLogin()
    {
        return this->login;
    }

private:
    std::string login;
    std::string password;
    std::string siteName;
};

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