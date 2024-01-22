#include<iostream>
using namespace std;

const int M = 1000000000;

int main(){
    int n, k; 
    cin>>n>>k; 
    int A[n+1]; 
    long long T[2][k+1];
    for (int i = 1; i <= n; i++)
        A[i] = 0; 
    for (int i = 0; i <= k; i++)
        T[1][i] = 1;
    
    A[1] = k+1;
    
    for (int i = 2; i <= n; i++){
        for (int j = 0; j <= k; j++){
            T[i%2][j] = T[(i+1)%2][j];

            if (j != k)
                T[i%2][j] += T[(i+1)%2][j+1]; 

            if (j != 0)
                T[i%2][j] += T[(i+1)%2][j-1];

            T[i%2][j] %= M;
            A[i] += T[i%2][j];
            A[i] %= M; 
        }
    }
    int index; 
    for (int i = 1; i <= n; i++){
        cin>>index; 
        cout<<A[index]<<" "; 
    }
    cout<<endl; 
        
}