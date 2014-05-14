#include "authentication.h"

/* Constructor: reads in the Data.dat file to see if there are any names */
/* and passwords currently in the file.					 */
/* tcgetattr gets the terminal attributes			 	 */
Authentication::Authentication()
{
    readFile();
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
}
/* Read in Data.dat to see if there are any usernames and passwords.	 */
/* Not that hard to understand.						 */
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

/* Takes in a vector of strings and splits them by a delimiter.		 */
/* The data is put in its respective map.				 */
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

/* Writes all usernames and passwords to Data.dat is a specific format,	 */
/* SHOCKER!								 */
void Authentication::writeFile() {
    ofstream file("Data.dat");

    if(file.is_open()) {
        for(unsigned int i = 0; i < m_username.size(); i++) {
            file << m_username[i] << "::" << m_password[i] << "\n";
        }
    }
}

/* Function to set up a new user. Input a name, check if its taken.	 */
/* If the name is not taken, goes to another function, validatePassword	 */
/* to get the password the user wants and returns the password		 */
/* Both password and username are inserted into their respective map.	 */
void Authentication::newUser() {
    string temp;
    cout << "Please choose a username:  ";
    cin >> temp;

    string name = checkUsername(temp);
    m_username.insert(pair<int, string>(m_username.size(), name));

    string password;
    password = validatePassword("Enter Password:  ", "\nRe-Enter Password:  ");

    m_password.insert(pair<int, string>(m_password.size(), password));
    writeFile();

    m_user = name;
}

/* The user already has a username and password. Checks the file if	 */
/* their login info can be found. User has the option to change password */
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

/* Allows the user to change their password. If yes, the user can change */
/* their password.							 */
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

/* Takes in the parameters mess1, mess2 to display different messages, 	 */
/* since this function is used by changePassword and newUser.		 */
/* Asks the user to input both passwords and checks if they are the same.*/
/* If they are the same it returns the password.			 */
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

/* Checks if the username is either taken or if the username could not	 */
/* be found. Used by newUser()						 */
string Authentication::checkUsername(string name) {
    bool isTaken;
    do {
        isTaken = false;

        for(unsigned int i = 0; i < m_username.size(); i++) {
            if(m_username[i] == name) {
                isTaken = true;
                cout << "\nThe username is already taken.\n\n";
            }
        }
        if(isTaken) {
            cout << "Username:  ";
            cin >> name;
        }
    } while (isTaken);

    return name;
}

/* Returns the user's username.						 */
string Authentication::getUserName() {
    return m_user;
}
