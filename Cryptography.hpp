#ifndef _CRYPTOGRAPHY_HPP_
#define _CRYPTOGRAPHY_HPP_

#include "Keys.hpp"

// Asymmetric Key Encryption, at leats a try at it
class Cryptography{
private:
    //Key object with the public and private key
    Keys _keys;
    std::string _fileName;
public:
    //Default constuctor
    Cryptography() : _fileName(""), _keys() {}

    Cryptography(std::string file) : _fileName(file), _keys() {}

    // Functions to encrypt and decrypt data in a file
    // Make maybe here encoder and decoder
    long long int encrypt(int message);
    long long int decrypt(int message);

    //Accessors
    //const std::string &getKey() const {return _key;}
    const std::string &getFile() const {return _fileName;}

    //Modifiers
    std::sting &getFile() {return _fileName;}

};
#endif // !_CRYPTOGRAPHY_HPP_
