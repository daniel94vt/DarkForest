#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

class Authentication
{
public:
    Authentication();

    void newUser();
    void login();
    string getUserName();

private:
    string m_user;
    termios oldt;
    termios newt;
    map<int, string> m_username;
    map<int, string> m_password;

    void readFile();
    void writeFile();
    void splitString(vector<string>);

    string checkUsername(string, string);
    string validatePassword(string, string);
    void changePassword(string);
};

#endif // AUTHENTICATION_H
