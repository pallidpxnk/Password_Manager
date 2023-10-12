#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <random>
#include <iomanip>

class PasswordManager
{
public:

    std::string generateStrongPassword();
    void createPasswordLog();
    void editPasswordEntry();
    void showAllPasswords();
    void printTitle();
    void setSiteName(std::string str);
    std::string getSiteName();

    void setPassword(std::string str);
    std::string getPassword();

    void setLogin(std::string str);
    std::string getLogin();

private:
    std::string login;
    std::string password;
    std::string siteName;
};

#endif