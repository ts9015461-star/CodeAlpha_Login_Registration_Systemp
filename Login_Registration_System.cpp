#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string FILE_NAME = "users.txt";

// Check whether username already exists
bool userExists(string username) {
    ifstream file(FILE_NAME);

    string savedUsername, savedPassword;

    while (getline(file, savedUsername, '|') &&
           getline(file, savedPassword)) {

        if (savedUsername == username) {
            return true;
        }
    }

    return false;
}

// Registration function
void registerUser() {

    string username, password;

    cout << "\n===== USER REGISTRATION =====\n";

    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter password: ";
    getline(cin, password);

    // Validate input
    if (username.empty() || password.empty()) {
        cout << "Error: Fields cannot be empty!\n";
        return;
    }

    if (username.find('|') != string::npos ||
        password.find('|') != string::npos) {
        cout << "Error: Special character '|' is not allowed!\n";
        return;
    }

    if (username.length() < 3) {
        cout << "Username must contain at least 3 characters!\n";
        return;
    }

    if (password.length() < 6) {
        cout << "Password must contain at least 6 characters!\n";
        return;
    }

    // Check duplicate username
    if (userExists(username)) {
        cout << "Error: Username already exists!\n";
        return;
    }

    // Store credentials in file
    ofstream file(FILE_NAME, ios::app);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    file << username << "|" << password << "\n";

    file.close();

    cout << "\nRegistration successful!\n";
}

// Login function
void loginUser() {

    string username, password;

    cout << "\n===== USER LOGIN =====\n";

    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter password: ";
    getline(cin, password);

    ifstream file(FILE_NAME);

    if (!file) {
        cout << "No registered users found!\n";
        return;
    }

    string savedUsername, savedPassword;

    bool loginSuccess = false;

    while (getline(file, savedUsername, '|') &&
           getline(file, savedPassword)) {

        if (savedUsername == username &&
            savedPassword == password) {

            loginSuccess = true;
            break;
        }
    }

    file.close();

    if (loginSuccess) {
        cout << "\nLogin successful!\n";
        cout << "Welcome, " << username << "!\n";
    }
    else {
        cout << "\nInvalid username or password!\n";
    }
}

// Main function
int main() {

    int choice;

    do {
        cout << "\n================================\n";
        cout << "     LOGIN AND REGISTRATION\n";
        cout << "================================\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "Enter your choice: ";

        string input;
        getline(cin, input);

        if (input == "1") {
            registerUser();
        }
        else if (input == "2") {
            loginUser();
        }
        else if (input == "3") {
            cout << "\nThank you for using the system!\n";
            break;
        }
        else {
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (true);

    return 0;
}
