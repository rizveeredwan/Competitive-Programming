#include <bits/stdc++.h>
using namespace std;
#define MAX_SIEVE 100000

//Sieve function
//MAX_SIEVE is the range till I will calculate my prime
//boolean array numbers[] and primes[] real primes
//primeCounter is the calculation of prime numbers
bool numbers[MAX_SIEVE+5];
int primes[MAX_SIEVE];
int primeCounter=-1;

void sieve() // the function begins
{
   for(int i=0;i<MAX_SIEVE;i++)
   {
       numbers[i]=true; // initialization everyone is prime
   }
   for(int i=4;i<MAX_SIEVE; i+= 2)
   {
       numbers[i] = false; // even numbers are not prime
   }
   int sqrtRoot = sqrt(MAX_SIEVE); // square root and it's an integer
   for(int i=3;i<sqrtRoot; i+= 2)
   {
       if(numbers[i] == true) // if it's a prime
       {
           for(int j = i * i; j <= MAX_SIEVE ; j += 2 * i)
           {
               numbers[j] = false; // all the multiples are not prime
           }
       }
   }
   primeCounter = 0;
   for(int i=2; i<=MAX_SIEVE ; i++)
   {
       if(numbers[i] == true) // if it's true  it's a prime
       {
           primeCounter++;
           primes[primeCounter] = i;
       }
   }
}

int main(void){
    sieve();
    cout<<numbers[2]<<" "<<numbers[3]<<" "<<numbers[4]<<endl;
    return 0;
}
