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
    void createLogin()
    {
        std::string loginName;
        std::cout << "\nEnter login(gmail): ";
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

    bool isFileEmpty(const std::string& filename) {
        std::ifstream file(filename);
        return file.peek() == std::ifstream::traits_type::eof();
    }

    void createPasswordLog()
    {
        if(isFileEmpty("login.txt"))
        {
            createLogin();
        }

        std::string inputSiteName;
        std::cout << "\nEnter site: ";
        std::cin >> inputSiteName;

        if (!std::cin) {
            std::cerr << "Error reading input for site name. Aborting." << std::endl;
            return;
        }

        setSiteName(inputSiteName);
        std::string inputPassword = generateStrongPassword();
        setPassword(inputPassword);

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
        
        fs << std::endl << "Site: " << getSiteName() << std::endl << "Login: " << outLogin << std::endl << "Password: " << getPassword() << std::endl;
        std::cout << std::endl << "Site: " << getSiteName() << std::endl << "Login: " << outLogin << std::endl << "Password: " << getPassword() << std::endl;
        char answer = 'n';
        std::cout << std::endl << "Continue? (y/n) ";
        std::cin >> answer;
        if (answer == 'y')
        {
            fs.close();
        }
        else
        {
            fs.close();
            exit(0);
        }
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
        std::cout << "2. Exit." << std::endl;
        std::cin >> k;
        switch(k)
        {
            case 1:
                system("clear");
                printTitle();
                pd.createPasswordLog();
                break;
            case 2:
                flag = false;
                exit(0);
                break;
        }
    }
        
    return 0;
}