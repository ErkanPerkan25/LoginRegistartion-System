#ifndef _KEYS_HPP_
#define _KEYS_HPP_

class Keys{
private:
    int _priKey;
    int _pubKey;
    int _n;
public:
    // Default constructor
    Keys();

    // Accessor and modifiers
    const int &getPubKey() const {return _pubKey;}
    const int &getpriKey() const {return _priKey;}
    const int &getN() const {return _n;}
};

#endif // !_KEYS_HPP_
