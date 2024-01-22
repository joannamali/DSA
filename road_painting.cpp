// used: segment tree with lazy propagation

#include <iostream>
#include<queue>
#include<vector>
using namespace std; 

vector<int> A; 
vector<int> V;  

void recursion(int a, int b, int w1, int w2, int nr, int color){
    if (A[nr] == color) return;

    if (a <= w1 && w2 <= b) { 
        A[nr] = color; 
        if (color == 0)
            V[nr] = w2 - w1 + 1;
        else 
            V[nr] = 0;
        
    return; 
    }

    if (b < w1 || a > w2)
        return; 
    if (A[nr] != -1){
        A[nr*2] = A[nr]; 
        A[nr*2+1] = A[nr]; 
        A[nr] = -1;  
        V[nr*2] = V[nr]/2;
        V[nr*2+1] = V[nr]/2;
    }

    recursion(a, b, w1, (w1+w2)/2, nr*2, color); 
    recursion(a, b, (w1+w2)/2+1, w2, nr*2+1, color); 
    V[nr] = V[nr*2] + V[nr*2+1];
}


int search(int z1, int z2, int nr){
    if (A[nr] == 0)  return z2-z1+1; 
    else if (A[nr] == 1)  return 0; 
    return search(z1, (z1+z2)/2, nr*2) + search((z1+z2)/2+1, z2, nr*2+1); 
}

int main(){
    int n, m; cin>>n>>m; 
    int len = 1; 
    while (len <= n)
        len *= 2; 

    for (int i = 0; i <= len*2; i++) {
        A.push_back(-1); 
        V.push_back(0); 
    }
    A[1] = 1; 


    for (int i = 0; i < m; i++){
        int a, b;
        char L; 
        cin>>a>>b>>L;

        L = L - 'B'; 
      // 1 - white, 0 - black

        recursion (a, b, 1, len, 1, L); 
        cout<<V[1]<<endl;
      

    }

}
