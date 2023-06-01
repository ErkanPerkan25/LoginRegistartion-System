/*************************************************************************
 * Author: Eric Hansson
 * File: main.cpp
 * Date: June 1 2023 - ...
 * Purpose: 
 *
**************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isLoggedIn(){
   string username, password, usr,pwd; 
   
   cout << "Enter Username: "; cin >> username;
   cout << "Enter Password: "; cin >> password;

   ifstream read("./" + username + ".txt");
   getline(read,usr);
   getline(read,pwd);

   if(username == usr && password == pwd){
       return true;
   }
   else{
       return false;
   }
}

void makeUser(string userName, string password){
    ofstream userFile;
    userFile.open("./" + userName + ".txt");
    userFile << userName << endl;
    userFile << password << endl;

    userFile.close();
}

int main (int argc, char *argv[]) {
    cout << "Welcome!" << endl;

    while (cin) {    
        cout << "Register(1) or Login(2)? Or 'exit' to end the program" << endl;

        string input;
        cin >> input;

        if(input == "1"){
            // Let the user register
            string newUser;
            string userPass1;
            string userPass2;

            cout << "Please enter in your username: ";
            cin >> newUser;

            cout << "Pleas enter in a password: ";
            cin >> userPass1;

            cout << "Please re-enter the password: ";
            cin >> userPass2;

            // If the password is not the same, re-do the password step
            if(userPass2 != userPass1){
                cout << "The passwords are not the same! Please try again." << endl;
            }
             
            if(userPass1 == userPass2){
                makeUser(newUser,userPass1);
                cout << "User successfully created!" << endl;
            }
        }

        else if(input == "2"){
            // Let the user login
            bool status = isLoggedIn();
            if(status == true){
                cout << "Successfully logged in!" << endl;
                return 0;
            }
            else{
                cout << "Incorrect Username or Pawssword!" << endl;
            }
        }

        else if(input == "exit"){
            return 0;
        }

        else{
            cout << "Please enter one of the command." << endl;
        }
    }

    return 0;
}
