/******************************************************************
 * Author: Eric Hansson
 * Date: June 2 2023
 * File: Cryptography.cpp
 * Purpose: Implement functions to encrypt files and decrypt them
 *
*******************************************************************/

#include "Cryptography.hpp"
#include <iostream>
#include <fstream>

using namespace std;

long long int
Cryptography::encrypt(int message){
    int e = _keys.getPubKey(); 
    long long int encryptedMessage = 1;
    while(e--){
        encryptedMessage *= message;
        encryptedMessage %= _keys.getN();
    }
    return encryptedMessage;
}

long long int
Cryptography::decrypt(int encryptMessage){
    int d = _keys.getpriKey();
    long long int decrypted = 1;
    while(d--){
        decrypted *= encryptMessage;
        decrypted %= _keys.getN();
    }
    return decrypted;
}
