#include "authentication.h"

Authentication::Authentication()
{
    readFile();
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    writeFile();
}

void Authentication::readFile() {
    ifstream file("Data.dat");

    if(!file.is_open()) {
        ofstream ofile("Data.dat");
        ofile.close();
    }

    vector<string> userData;
    string line;

    file.is_open();
    while(getline(file, line)) {
        userData.push_back(line);
    }
    file.close();
    splitString(userData);
}

void Authentication::splitString(vector<string> data) {
    string delimiter = "::";
    for(unsigned int i = 0; i < data.size(); i++) {
        size_t pos = 0;
        while((pos = data[i].find(delimiter)) != string::npos) {
            m_username[i] = data[i].substr(0,pos);
            data[i].erase(0,pos + delimiter.length());
        }
        m_password[i] = data[i];
    }
}

void Authentication::writeFile() {
    ofstream file("Data.dat");

    if(file.is_open()) {
        for(unsigned int i = 0; i < m_username.size(); i++) {
            file << m_username[i] << "::" << m_password[i] << "\n";
        }
    }

}

void Authentication::newUser() {
    string temp;
    cout << "Please choose a username:  ";
    cin >> temp;

    string name = checkUsername(temp, "\nThe username is already taken.\n\n");
    m_username.insert(pair<int, string>(m_username.size(), name));

    string password;
    password = validatePassword("Enter Password:  ", "\nRe-Enter Password:  ");

    m_password.insert(pair<int, string>(m_password.size(), password));
    writeFile();

    m_user = name;
}

void Authentication::login() {
    readFile();
    bool correctInfo;
    string name;
    string password;

    do {
        correctInfo = false;
        cout << "Username:  ";
        cin >> name;

        for(unsigned int i = 0; i < m_username.size(); i++) {
            if(m_username[i] == name) {
                do {
                    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
                    cout << "Password:  ";
                    cin >> password;

                    if(password != m_password[i])
                        cout << "\nIncorrect password.\n";
                } while(m_password[i] != password);

                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                correctInfo = true;
                cout << endl;
            }
        }
        if(!correctInfo)
            cout << "\nThe username cannot be found.\n";
    }while(!correctInfo);
    m_user = name;

    changePassword(name);
}

void Authentication::changePassword(string name) {
    char ans;
    string password;
    do {
        cout << "Do you want to change your password (y/n):  ";
        cin >> ans;
    } while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');

    if(ans == 'y' || ans == 'Y') {
        password = validatePassword("Enter New Password:  ", "\nRe-Enter New Password:  ");
        for(unsigned int i = 0; i < m_username.size(); i++) {
            if(m_username.at(i) == name)
                m_password.at(i) = password;
        }
        writeFile();
    }
}

string Authentication::validatePassword(string mess1, string mess2) {
    string pass1, pass2;
    do {
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        cout << mess1;
        cin >> pass1;

        cout << mess2;
        cin >> pass2;

        if(pass1 != pass2) {
            cout << "\nYour passwords do not match.\n\n";
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    } while (pass1 != pass2);
    cout << endl;

    return pass1;
}

string Authentication::checkUsername(string name, string message) {
    bool isTaken;
    do {
        isTaken = false;

        for(unsigned int i = 0; i < m_username.size(); i++) {
            if(m_username[i] == name) {
                isTaken = true;
                cout << message;
            }
        }
        if(isTaken) {
            cout << "Username:  ";
            cin >> name;
        }
    } while (isTaken);

    return name;
}

string Authentication::getUserName() {
    return m_user;
}
