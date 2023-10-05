#include <iostream>
#include <string>
#include <fstream>

class PasswordGenerator
{
public:
    void CreateLogin()
    {
        std::string loginName;
        std::cout << "\nEnter login: ";
        std::cin >> loginName;
        SetLogin(loginName);

        std::string path = "login.txt";
        std::fstream fs;
        fs.open(path, std::fstream::out);
        fs << GetLogin();
    }

    void CreatePasswordLog()
    {
        std::string inputSiteName;
        std::cout << "\nEnter site: ";
        std::cin >> inputSiteName;
        SetSiteName(inputSiteName);

        std::string inputPassword;
        std::cout << "\nEnter password: ";
        std::cin >> inputPassword;
        SetPassword(inputPassword);

        std::string path = "passwords.txt";
        std::string loginPath = "login.txt";
        std::fstream fs, fs1;
        fs.open(path, std::fstream::out);
        fs1.open(loginPath, std::fstream::in);
        std::string outLogin;
        while(!fs1.eof())
        {
            fs1 >> outLogin;
        }
        SetLogin(outLogin);
        fs << "Site: " << GetSiteName() << std::endl << "Login: " << GetLogin() << std::endl << "Password: " << GetPassword();
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


int main()
{
    PasswordGenerator pd;
    //pd.CreateLogin();
    pd.CreatePasswordLog();
    return 0;
}