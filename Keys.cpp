/********************************************************************************
 * Author: Eric Hansson
 * File: Keys.cpp
 * Date: June 2 2023
 * Purpose: To generate keys
*********************************************************************************/
#include "Keys.hpp"
#include <cstdlib>
#include <set>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

set<int> primeNumbers;    

// Sieve of Eratosthenes used with a set
void primeList(int n){
    // Creates a list of all number from 1 to n (input)
    for(int i = 2; i <= n; i++){
        primeNumbers.insert(i);
    }

    // Goes through the list of numbers and 
    for(int i = 2; i < primeNumbers.size();i++){
        for(int j = i; j <= n; j++){
            primeNumbers.erase(j*i);
        }
    }

}

// Function to pick a random prime number from the list and delete if from the list
int randomPrime(){
    //
    int k = rand() % primeNumbers.size();
    // Takes the beginning of the prime numbers
    auto it = primeNumbers.begin();

    // Goes from the random number and goes from begin and end
    while(k--)
        it++;

    // Stores the prime number
    int ret = *it;
    // Ereases the prime number from the list
    primeNumbers.erase(it);

    // Return the choosen prime number
    return ret;
    
}

Keys::Keys(){
    primeList(100);
    // Picks two random prime numbers
    int p = randomPrime();
    int q = randomPrime();
    // Calculates the modulus (n) which is used to the public and private key
    _n = p*q;

    // Calcualtes the Labmabd(n)
    int phi = lcm((p-1),(q-1));
    int e = 2;

    // Gets the comprime for phi
    while(1){
        if(__gcd(e,phi)==1)
            break;
        e++;
    }
    // Public key
    _pubKey = e;

    // Gets the modular multiplictive inverse
    int d = 2;
    while(1){
        if((d*e) % phi == 1)
            break;
        d++;
    }
    // Private key
    _priKey = d;

}
