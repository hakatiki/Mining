#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <random>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <unordered_set>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <chrono>

using namespace std;
unsigned int n, p;
// elso a tavolsag;
unsigned long long int arr[5001][2];
unsigned long long int cost[5002][5002];
unsigned long long int mini[5002][5002];

unsigned long long int partition(unsigned  int cuts, unsigned  int lastcut){
    unsigned long long int minimum = numeric_limits<unsigned long long int>::max();
    ++cuts;
    if(p != cuts){
        for(unsigned int i = lastcut, j = i + 1; i < n - (p-cuts)&&mini[lastcut][i]<minimum ; ++i, ++j ){
            if(cost[cuts][j]!= -1)
                minimum = min(minimum,cost[cuts][j] + mini[lastcut][i]);
            else
                minimum = min(minimum,partition(cuts,j) + mini[lastcut][i]);
        }
        cost[cuts-1][lastcut] = minimum;
        return minimum;
    }
    return mini[lastcut][n-1];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    auto b = chrono::high_resolution_clock::now();
    ifstream in("/Users/takatsbalint/Documents/Projects/Mining/Mining/base.txt");
    in >> n >> p;
    for (unsigned int i = 0; i < n; ++i)
        in >> arr[i][0] >> arr[i][1];
    
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 1; j <=i; ++j) {
            cost[i][j] = cost[i][j - 1] + (arr[i][0] - arr[j - 1][0])*arr[j - 1][1];
        }
        for (unsigned int j = i+1; j < n + 1; ++j) {
            cost[i][j] = cost[i][j - 1] + (arr[j - 1][0]-arr[i][0] )*arr[j - 1][1];
        }
    
    }
    auto m =chrono::high_resolution_clock::now();
    //cout << chrono::duration_cast<chrono::milliseconds>(m-b).count()<<"\n";
    
    //memset(mini, -1 , sizeof(mini[0][0])*5002*5002);
    unsigned long long int diff;
    bool quit;
    for (unsigned int i = 0; i < n; ++i) {
        unsigned int last_pos = i;
        mini[i][i] = 0;
        for (unsigned int j = i + 1; j < n; ++j) {
            quit = false;
            mini[i][j] = numeric_limits<unsigned long long int>::max();
            diff =cost[last_pos][j+1] - cost[last_pos][i];
            for (unsigned int k = last_pos; k <= j; ++k) {
                diff = cost[k][j+1] - cost[k][i];
                if(mini[i][j] > diff){
                    mini[i][j] = diff;
                    last_pos = k;
                    quit = true;
                }
               else if(quit == true)
                   break;
            }
        }
    }
    for(unsigned int i = 0; i < p; ++i)
        memset(cost[i], -1, sizeof(cost[0][0])*n);
    
    auto mm =chrono::high_resolution_clock::now();
    //cout << chrono::duration_cast<chrono::milliseconds>(mm-m).count()<<"\n";

    cout << partition(0,0)<< "\n";
    auto e =chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(e-mm).count()<<"\n";
    cout << chrono::duration_cast<chrono::milliseconds>(e-b).count()<<"\n";
    
    //system("pause");
}
