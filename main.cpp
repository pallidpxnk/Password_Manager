#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <random>

class PasswordManager
{
public:
    void CreateLogin()
    {
        std::string loginName;
        std::cout << "\nEnter login: ";
        std::cin >> loginName;
        
        if (!std::cin) {
            std::cerr << "Error reading input. Aborting." << std::endl;
            return;
        }

        std::string path = "login.txt";
        std::fstream fs;
        fs.open(path, std::fstream::out);

        if (!fs.is_open()) {
            std::cerr << "Error opening file " << path << ". Aborting." << std::endl;
            return;
        }

        fs << loginName << std::endl;

        fs.close();
    }

    std::string generateStrongPassword() {
        const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
        const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const std::string numbers = "0123456789";
        const std::string specialChars = "!@#$%^&*()_+-=[]{}|;:,.<>?";

        // Create a pool of characters for the remaining part of the password
        const std::string remainingChars = lowercase + lowercase + lowercase;

        srand(time(0));

        // Create the password with the required characters
        std::string password;
        password.push_back(uppercase[rand() % uppercase.length()]);
        password.push_back(numbers[rand() % numbers.length()]);
        password.push_back(specialChars[rand() % specialChars.length()]);
        password.push_back(uppercase[rand() % uppercase.length()]);
        password.push_back(numbers[rand() % numbers.length()]);
        password.push_back(specialChars[rand() % specialChars.length()]);
        password.push_back(uppercase[rand() % uppercase.length()]);
        password.push_back(numbers[rand() % numbers.length()]);
        password.push_back(specialChars[rand() % specialChars.length()]);

        // Calculate the remaining length
        int remainingLength = 24;

        // Fill the rest of the password with random characters
        for (int i = 0; i < remainingLength; ++i) {
            password.push_back(remainingChars[rand() % remainingChars.length()]);
        }

        std::random_shuffle(password.begin(), password.end());

        return password;
    }

    void createPasswordLog()
    {
        std::string inputSiteName;
        std::cout << "\nEnter site: ";
        std::cin >> inputSiteName;

        if (!std::cin) {
            std::cerr << "Error reading input for site name. Aborting." << std::endl;
            return;
        }

        SetSiteName(inputSiteName);
        std::string inputPassword = generateStrongPassword();
        SetPassword(inputPassword);

        std::string loginPath = "login.txt";
        std::fstream fs1;
        fs1.open(loginPath, std::fstream::in);

        if (!fs1.is_open()) {
            std::cerr << "Error opening file " << loginPath << ". Aborting." << std::endl;
            return;
        }

        std::string outLogin;
        while(!fs1.eof())
        {
            fs1 >> outLogin;
        }

        fs1.close();

        std::string path = "passwords.txt";
        std::fstream fs;
        fs.open(path, std::fstream::out | std::fstream::app);

        if (!fs.is_open()) {
            std::cerr << "Error opening file " << path << ". Aborting." << std::endl;
            return;
        }
        
        fs << std::endl << "Site: " << GetSiteName() << std::endl << "Login: " << outLogin << std::endl << "Password: " << GetPassword() << std::endl;

        fs.close();
    }

    void SetSiteName(std::string str)
    {
        this->siteName = str;
    }
    std::string GetSiteName()
    {
        return this->siteName;
    }

    void SetPassword(std::string str)
    {
        this->password = str;
    }
    std::string GetPassword()
    {
        return this->password;
    }

    void SetLogin(std::string str)
    {
        this->login = str;
    }
    std::string GetLogin()
    {
        return this->login;
    }

private:
    std::string login;
    std::string password;
    std::string siteName;
};

void PrintTitle()
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
        PrintTitle();
        std::cout << "1. Enter login." << std::endl;
        std::cout << "2. Generate password." << std::endl;
        std::cout << "3. Exit." << std::endl;
        std::cin >> k;
        switch(k)
        {
            case 1:
                system("clear");
                PrintTitle();
                pd.CreateLogin();
                break;
            case 2:
                system("clear");
                PrintTitle();
                pd.createPasswordLog();
                break;
            case 3:
                flag = false;
                exit(0);
                break;
        }
    }
        
    return 0;
}