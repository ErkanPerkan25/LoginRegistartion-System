/********************************************************************************
 * Author: Eric Hansson
 * File: Keys.cpp
 * Date: June 2 2023
 * Purpose: To generate keys
*********************************************************************************/
#include "Keys.hpp"
#include <set>
#include <iostream>

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
void randomPrime(){
    int k = rand() % primeNumbers().size();

}
