// used: segment tree

#include<iostream>
using namespace std; 

#define M 1000000000

void balance(int (&D)[], int n){
    while (n != 1){
        n /= 2; 
        D[n] = D[n*2] + D [n*2 + 1];
        D[n] %= M; 
    } 
}

int search (int (&D)[], int n, int cur, int a, int b){
    if (b <= n)
        return 0; 
    if (a > n)
        return D[cur]; 

    return (search(D, n, cur * 2, a, (a+b)/2) + search (D, n, cur * 2 + 1, (a+b)/2+1, b)) % M;

}

int main(){
    int n, k; 
    cin>>n>>k; 
    int data[n];  
    for (int i = 0; i < n; i++){
        cin>>data[i]; 
    }

    int d_size = 2; 
    while (d_size < n)
        d_size *= 2; 
    
    int D[k+1][d_size*2]; 

    for (int i = 1; i < k+1; i++)
        for (int j = 1; j < d_size*2; j++)
            D[i][j] = 0; 

    int leaves = d_size; 

    for (int l = 0; l < n; l++)
        for (int i = 1; i <= k; i++){  
            int pos = leaves + data[l] - 1; 
            if (i == 1)
                D[i][pos] = 1; 
            else 
                D[i][pos] = search (D[i-1], data[l], 1, 1, d_size) % M;

            balance (D[i], pos);
        }

    cout<<D[k][1]<<endl; 

}

