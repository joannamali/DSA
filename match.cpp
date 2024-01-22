#include<iostream>
#include<set>
using namespace std; 

int main(){
    
    int n, m; cin>>n>>m;
    int A[m][n]; 
    long long T[n]; 

    for (int i = 0; i < n; i++)
        T[i] = 0; 

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin>>A[i][j];

    set<long long> S;
    

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            T[A[i][j]-1] = T[A[i][j]-1]<<1;
            if (j < n/2){
                T[A[i][j]-1]++; 
            }
        }
    }
    for (int i = 0; i < n; i++){
        if (S.count(T[i])){
            cout<<"NO"<<endl; 
            return 0;
        }
        else {
            S.insert(T[i]);
        }
    }
    cout<<"YES"<<endl; 

    
}
