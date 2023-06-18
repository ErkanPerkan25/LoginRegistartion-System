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

#include "Keys.hpp"

using namespace std;

// Function to check if the user is logged in
bool isLoggedIn(){
   string username, password, usr,pwd; 
   
   // Enterns in the username and password
   cout << "Enter Username: "; cin >> username;
   cout << "Enter Password: "; cin >> password;

   // Gets the file of the username
   ifstream read("./" + username + ".txt");
   getline(read,usr);
   getline(read,pwd);

   // If both the username and passowrd are the same as file woth login info
   if(username == usr && password == pwd){
       return true;
   }
   // Otherwise not the same username or password
   else{
       return false;
   }
}

// Function to make a user and a file to store the user information
void makeUser(string userName, string password){
    ofstream userFile;
    // Makes the file with the username
    userFile.open("./" + userName + ".txt");
    // Reads in the username and password in to the file
    userFile << userName << endl;
    userFile << password << endl;

    // Closed the file
    userFile.close();
}

int main (int argc, char *argv[]) {
    cout << "Welcome!" << endl;

    Keys keys;
    // Debugging to see the public key
    //cout << keys.getpriKey() << endl;

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
