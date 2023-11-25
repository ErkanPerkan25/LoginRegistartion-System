/************************************************************************
 * Author: Eric Hansson
 * File: main.cpp
 * Date: June 1 2023 - ...
 * Purpose: 
 *
**************************************************************************/
#include <iostream>
#include <fstream>
#include <openssl/rsa.h>
#include <string>
#include <vector>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/conf.h>
#include <openssl/rand.h>

#include "Keys.hpp"

using namespace std;

EVP_PKEY *generateKeyPair(){
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);

    if (!ctx) {
        std::cerr << "Failed to create EVP_PKEY_CTX" << endl;
    }

    if(EVP_PKEY_keygen_init(ctx) <= 0){
        std::cerr << "Failed to create EVP_PKEY_keygen_init" << endl;
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }

    if(EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0){
        std::cerr << "Failed to set key length" << endl;
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }

    EVP_PKEY *key = nullptr;

    if(EVP_PKEY_generate(ctx, &key) <= 0){
        std::cerr << "Failed to generate key pair" << endl;
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }

    EVP_PKEY_CTX_free(ctx);
    return key;
}

// Function to encrypt 
bool encrypt(const unsigned char *plainText, int plainTextLen, const unsigned char *key, const unsigned *iv
            , unsigned char *cipherTex, int &cipherTextLen){

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx){
        cerr << "Failed to create EVP_CHIPER_CTX" << endl;
        return false;
    }

    if(EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key, iv) != 1){
        cerr << "Failed to initialize encryption" << endl;
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if(EVP_EncryptUpdate(ctx, cipherTex, &cipherTextLen, plainText, plainTextLen) != 1){
        cerr << "Failed to encrypt data" << endl;
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    EVP_CIPHER_CTX_free(ctx);
    return true;
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
   //vector<int> usr;
   //vector<int> pwd;
   
   // Enterns in the username and password
   cout << "Enter Username: "; cin >> username;
   cout << "Enter Password: "; cin >> password;
  
   // Gets the file of the username
   ifstream read("./" + username + ".txt");
  /* 
   // PROBLEM MIGHT BE HERE
   if(read.is_open()){
       string line;
       while(getline(read,line)){
           int letter = stoi(line);
           if(line.empty()){
               pwd.push_back(letter);
           }
           usr.push_back(letter);
       }
   }

   for(auto& num : user)
       usr.push_back(num-'0');

   for(auto& num : pass)
       pwd.push_back(num-'0');
*/ 
   getline(read,user);
   getline(read,pass);
   
   // If both the username and password are the same as file woth login info
   if(username == user && password == pass){
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
   
    /*
    vector<int> usr = encoder(userName, keys);
    vector<int> psw = encoder(password, keys);
    
    for(auto& content : usr){
        userFile << content << endl;
    }
    userFile << endl;

    for(auto& content : psw){
        userFile << content << endl;
    }
    */  
    userFile << userName << endl;
    userFile << password << endl;

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
