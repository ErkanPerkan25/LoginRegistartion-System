#ifndef _CRYPTOGRAPHY_HPP_
#define _CRYPTOGRAPHY_HPP_

// Asymmetric Key Encryption, at leats a try at it
class Cryptography{
private:
   // Private key 
   // int or string priKey;
   string key;
public:
    // Public key
    // int or string pubKey;
    void encrypt();
    void decrypt();

};
#endif // !_CRYPTOGRAPHY_HPP_
