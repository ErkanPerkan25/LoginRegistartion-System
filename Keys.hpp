#ifndef _KEYS_HPP_
#define _KEYS_HPP_

class Keys{
private:
    int _priKey;
    int _pubKey;
public:
    // Default constructor
    Keys();

    // Accessor and modifiers
    const int &getPubKey() const {return _pubKey;}
    //int &getPubKey() {return _pubKey;}
};

#endif // !_KEYS_HPP_
