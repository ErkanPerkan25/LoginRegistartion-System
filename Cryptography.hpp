#ifndef _CRYPTOGRAPHY_HPP_
#define _CRYPTOGRAPHY_HPP_

// Asymmetric Key Encryption, at leats a try at it
class Cryptography{
private:
   // Private key 
   // int or string priKey;
    //int _pubKey;
    //int _priKey;
    std::string _fileName;
public:
    // Public key
    // int or string pubKey;
    void encrypt();
    void decrypt();

    //Accessors
    //const std::string &getKey() const {return _key;}
    const std::string &getFile() const {return _fileName;}

    //Modifiers
    std::sting &getFile() {return _fileName;}

};
#endif // !_CRYPTOGRAPHY_HPP_
