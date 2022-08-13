#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef long long int ll;

//function 1 O(n/2)
vector<int>is_Prime_num(10000011,1);
bitset<500001> Primes;
void prime_number(ll n){
    is_Prime_num[0]=0, is_Prime_num[1]=0;
    for(ll i=2; i<=n; i+=2){
        if(i==2)continue;
        is_Prime_num[i]=0;
    }
    for(ll i=3; i*i<=n; i+=2){
        if(i==3)continue;
        else if(is_Prime_num[i]==1){
            for(ll j=i*i; j<=n; j+=2*i){
                is_Prime_num[j]=0;
            }
        }
    }
}

void SieveOfEratosthenes(int n)
{
    //function 2 O(n*log(log(n)))
    Primes[0] = 1;
    for (int i = 3; i*i <= n; i += 2) {
        if (Primes[i / 2] == 0) {
            for (int j = i * i; j <= n; j += 2 * i)
                Primes[j / 2] = 1;
        }
    }
}


int main(void){
    // Get starting timepoint
    auto start = high_resolution_clock::now();
    SieveOfEratosthenes(1000000);
    //prime_number(1000000);
    // Get ending timepoint
    auto stop = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
   return 0;
}
