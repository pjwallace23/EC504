
// C++ program for implementation of KMP pattern searching 
// algorithm 
#include <iostream>
using namespace std;

#include "KMP.h"

  
// Driver program to test above function 
int main() 
{ 
    string txt = "ABRACADABRA"; 
    string pat = "ABRACADABRA"; 
    KMPSearch(pat, txt); 
    return 0; 
} 
