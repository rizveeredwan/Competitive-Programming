#include <bits/stdc++.h>
using namespace std;
#define MAX_SIEVE 100000

//Sieve function
//MAX_SIEVE is the range till I will calculate my prime
//boolean array numbers[] and primes[] real primes
//primeCounter is the calculation of prime numbers
bool numbers[MAX_SIEVE+5];
vector<int>primes;

void sieve() // the function begins
{
   for(int i=0;i<MAX_SIEVE;i++)
   {
       numbers[i]=true; // initialization everyone is prime
   }
   primes.push_back(2);
   for(int i=4;i<MAX_SIEVE; i+= 2)
   {
       numbers[i] = false; // even numbers are not prime
   }
   int sqrtRoot = sqrt(MAX_SIEVE); // square root and it's an integer
   for(int i=3;i<sqrtRoot; i+= 2)
   {
       if(numbers[i] == true) // if it's a prime
       {
           primes.push_back(i);
           for(int j = i * i; j <= MAX_SIEVE ; j += 2 * i)
           {
               numbers[j] = false; // all the multiples are not prime
           }
       }
   }
}

bool prime_checking(int n){
    int sq = sqrt(n);
    //cout<<"sq ="<<sq<<endl;
    for(int i=0;i<primes.size() && primes[i]<=sq; i++){
        //cout<<primes[i]<<" "<<primes[i]<<" "<<n%primes[i]<<endl;
        if(n%primes[i] == 0) return false; // not prime
    }
    return true;
}

void test_case_generation(){
    int st=300000000;
    for(int i = st; i<=st+100000; i++){
        if(prime_checking(i) == true) {
            cout<<"found "<<i<<endl;
            //return;
        }
    }
    return;
}

int main(void){
    sieve();
    test_case_generation();
    int t;
    cin>>t;
    int n;
    bool verdict;
    for(int i=0;i<t;i++){
        cin>>n;
        verdict = prime_checking(n);
        if(n == true) cout<<"PRIME"<<endl;
        else cout<<"NOT PRIME"<<endl;
    }
    return 0;
}
