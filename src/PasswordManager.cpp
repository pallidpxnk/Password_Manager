#include "PasswordManager.h"

std::string PasswordManager::generateStrongPassword() {
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

void PasswordManager::modifyLogin(const std::string& login, const std::string& siteName) {
    std::string gmailSuffix = "@gmail.com";
    if (login.size() >= gmailSuffix.size() &&
        login.compare(login.size() - gmailSuffix.size(), gmailSuffix.size(), gmailSuffix) == 0) {
        std::string modifiedLogin = login;
        modifiedLogin.insert(modifiedLogin.size() - gmailSuffix.size(), "+" + siteName);
        setLogin(modifiedLogin);
    }
}

void PasswordManager::createPasswordLog()
{
    bool flag = true;
    while (flag)
    {
        system("clear");
        printTitle();
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

        modifyLogin(getLogin(), getSiteName());
        
        std::string inputPassword = generateStrongPassword();
        setPassword(inputPassword);

        std::string path = "../passwords/passwords.txt";
        std::fstream fs;
        fs.open(path, std::fstream::out | std::fstream::app);

        if (!fs.is_open()) {
            std::cerr << "Error opening file " << path << ". Aborting." << std::endl;
            return;
        }
        
        std::cout << std::endl << "Site: " << getSiteName() << std::endl << "Login: " << getLogin() << std::endl << "Password: " << getPassword() << std::endl;
        
        std::string answer;
        while (true) {
            std::cout << std::endl << "Edit or Continue or move back? (e/c/m) ";
            std::cin >> answer;

            if (answer == "e") {
                editPasswordEntry();
                fs << std::endl << "Site: " << getSiteName() << std::endl << "Login: " << getLogin() << std::endl << "Password: " << getPassword() << std::endl;
                fs.close();
                flag = false;
                break;
            } else if (answer == "c") {
                fs << std::endl << "Site: " << getSiteName() << std::endl << "Login: " << getLogin() << std::endl << "Password: " << getPassword() << std::endl;
                fs.close();
                break;
            } else if (answer == "m"){
                fs << std::endl << "Site: " << getSiteName() << std::endl << "Login: " << getLogin() << std::endl << "Password: " << getPassword() << std::endl;
                fs.close();
                flag = false;
                break;
            } else {
                std::cout << "Invalid input. Please enter 'e' to edit or 'c' to continue or 'm' to move back." << std::endl;
            }
        }
    }
}

void PasswordManager::editPasswordEntry() 
{
    system("clear");
    printTitle();
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

void PasswordManager::showAllPasswords() {
    std::string path = "../passwords/passwords.txt";
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << path << ". Aborting." << std::endl;
        return;
    }

    std::string line;

    std::cout << std::endl;
    std::cout << std::left << std::setw(35) << "Site" << std::setw(35) << "Login" << std::setw(35) << "Password" << std::endl;
    std::cout << std::string(101, '-') << std::endl;

    while (std::getline(file, line)) {
        if (line.find("Site: ") != std::string::npos) {
            std::string siteName = line.substr(6);
            std::string login, password;

            if (std::getline(file, login) && std::getline(file, password)) {
                login = login.substr(7);
                password = password.substr(10);

                std::cout << std::left << std::setw(35) << siteName << std::setw(35) << login << std::setw(35) << password << std::endl;
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

void PasswordManager::printTitle()
{
    std::cout << "⌜⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⌝" << std::endl;
    std::cout << "|                      Password Manager                        |" << std::endl;
    std::cout << "⌞₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋₋⌟" << std::endl;
}

void PasswordManager::setSiteName(std::string str)
{
    this->siteName = str;
}
std::string PasswordManager::getSiteName()
{
    return siteName;
}

void PasswordManager::setPassword(std::string str)
{
    this->password = str;
}
std::string PasswordManager::getPassword()
{
    return password;
}

void PasswordManager::setLogin(std::string str)
{
    this->login = str;
}
std::string PasswordManager::getLogin()
{
    return login;
}