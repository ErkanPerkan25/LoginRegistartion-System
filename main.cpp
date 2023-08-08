/************************************************************************
 * Author: Eric Hansson
 * File: main.cpp
 * Date: June 1 2023 - ...
 * Purpose: 
 *
**************************************************************************/
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Keys.hpp"

using namespace std;

//Keys keys;

// Function to encrypt data
long long int encrypt(int data, Keys keys){
    int e = keys.getPubKey();
    long long int encrypt = 1;
    while(e--){
        encrypt *= data;
        encrypt %= keys.getN();
    }
    return encrypt;
}

// Function to decrypt data
long long int decrypt(int encryptData, Keys keys){
    int d = keys.getpriKey();
    long long int decrypt = 1;
    while(d--){
        decrypt *= encryptData;
        decrypt %= keys.getN();
    }
    return decrypt;
}

vector<int> encoder(string data, Keys keys){
    // Takes the data (string) and turn in to cipher (int)
    vector<int> cipher;
    for(auto& letter : data){
        cipher.push_back(encrypt((int)letter, keys));
    }
    return cipher;
}

string decoder(vector<int> cipher, Keys keys){
    // Takes the data which is numbers(int) and turn to plain text
    string data;

    for(auto& number : cipher){
       data += decrypt(number, keys);
    }
    return data;
}

// Function to check if the user is logged in
// Problem is that there is no vector where the right letter is but in the vector
// And i don't know how to get the same encoded format when pulling the information
// from the file
bool isLoggedIn(Keys keys){
   string username, password, user, pass; 
   vector<int> usr;
   vector<int> pwd;
   
   // Enterns in the username and password
   cout << "Enter Username: "; cin >> username;
   cout << "Enter Password: "; cin >> password;
  
   // Gets the file of the username
   ifstream read("./" + username + ".txt");
   
   if(read.is_open()){
       char letter;
       while(read){
           usr.push_back(letter);
       }
   }
   // PROBLEM MIGHT BE HERE
   /*
   getline(read,user);
   getline(read,pass);

   for(auto& num : user)
       usr.push_back(num-'0');

   for(auto& num : pass)
       pwd.push_back(num-'0');

   */
   // If both the username and password are the same as file woth login info
   if(username == decoder(usr,keys) && password == decoder(pwd,keys)){
       return true;
   }
   // Otherwise not the same username or password
   else{
       return false;
   }
}

// Function to make a user and a file to store the user information
void makeUser(string userName, string password, Keys keys){
    ofstream userFile;
    // Makes the file with the username
    userFile.open("./" + userName + ".txt");
    // Reads in the username and password in to the 
    // Encrypts the username and password
    
    vector<int> usr = encoder(userName, keys);
    vector<int> psw = encoder(password, keys);
    
    for(auto& content : usr){
        userFile << content << endl;
    }
    userFile << endl;

    for(auto& content : psw){
        userFile << content << endl;
    }
     
    //userFile << userName << endl;
    //userFile << password << endl;

    // Closed the file
    userFile.close();
}

int main (int argc, char *argv[]) {
    cout << "Welcome!" << endl;

    Keys keys;
    // Debugging to see the public key
    //cout << keys.getPubKey() << endl;

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
                makeUser(newUser,userPass1, keys);
                cout << "User successfully created!" << endl;
            }
        }

        else if(input == "2"){
            // Let the user login
            bool status = isLoggedIn(keys);
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
