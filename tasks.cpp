#include<iostream>
#include<vector>
#include<algorithm>
#include <queue>
using namespace std; 

int main(){
    int n, m, k; cin>>n>>m>>k; 
    vector<int> G[n+1]; 
    pair<int, int> W[n]; 
    int A[n+1];

    for (int i = 0; i < n; i++){
        cin>>W[i].first; 
        A[i+1] = 0; 
        W[i].second = i + 1;
    }

    sort(W, W + n, greater<pair<int, int>>());

    int a, b; 
    for (int i = 0; i < m; i++){
        cin>>a>>b; 
        G[b].push_back(a); 
    }

    for (int i = 0; i < n; i++){
        int weight = W[i].first; 
        queue<int> Q; 
        Q.push(W[i].second);
        while (!Q.empty()){
            int t = Q.front(); 
            Q.pop(); 
            if (A[t] != 0)
                continue;
            
            A[t] = weight; 
            for (int a : G[t])
                Q.push(a); 
        }
    }


    sort(A + 1, A + 1 + n);
    cout<<A[k]<<endl; 

}
