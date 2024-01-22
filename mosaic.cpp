#include<iostream>
#include<cmath>
using namespace std; 

int main(){
    int n; cin>>n; 
    int A[n]; 
    const int MLD = pow(10, 9);
    for (int i = 0; i < n; i++)
        cin>>A[i]; 

    int LP[n][n][2]; 

    for (int i = 0; i < n; i++){
        LP[i][i][0] = 1; 
        LP[i][i][1] = 0; 
    }

    for (int d = 1; d < n; d++){
        for (int j = 0; j+d < n; j++){
            LP[j][j+d][0] = 0; 
            LP[j][j+d][1] = 0; 

            if (A[j] < A[j+1])
                LP[j][j+d][0] += LP[j+1][j+d][0];  
            if (A[j] < A[j+d])
                LP[j][j+d][0] += LP[j+1][j+d][1];  

            LP[j][j+d][0] %= MLD;            
            

            if (A[j+d] > A[j])
                LP[j][j+d][1] += LP[j][j+d-1][0];   
            if (A[j+d] > A[j+d-1])
                LP[j][j+d][1] += LP[j][j+d-1][1];             
            
            LP[j][j+d][1] %= MLD; 
        }

    }
    cout<<(LP[0][n-1][0] + LP[0][n-1][1])%MLD<<endl; 

    

}