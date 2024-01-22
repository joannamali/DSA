// used: Dijkstra's algorithm

#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
#include<queue>
#include<climits>
using namespace std; 

#define para pair<int, int>

bool sortbysec(const tuple<int, int, int>& a,  
               const tuple<int, int, int>& b) 
{ 
    return (get<1>(a) < get<1>(b)); 
}

int main(){
    int n; cin>>n; 
    pair<int, int> A[n]; 
    vector<tuple<int, int, int>> B; 
    for (int i = 0; i < n; i++){
        cin>>A[i].first>>A[i].second;
        B.push_back(make_tuple(A[i].first, A[i].second, i));
    }

    vector<pair<int, int>> G[n];   
    
    sort(B.begin(), B.end());

    for (int i = 0; i < n; i++){
        int index = get<2>(B[i]);
        
        if (i != 0){
            int prev_index = get<2>(B[i-1]);
            pair<int, int> cur = A[index];  
            pair<int, int> prev = A[prev_index];
            int dist = cur.first - prev.first;
            G[index].push_back(make_pair(dist, prev_index));
        }
        if (i!= n-1){
            int next_index = get<2>(B[i+1]);
            pair<int, int> cur = A[index];  
            pair<int, int> next = A[next_index];
            int dist = next.first - cur.first;
            G[index].push_back(make_pair(dist, next_index));
        }
    }
    

    sort(B.begin(), B.end(), [](tuple<int, int, int> x, tuple<int, int, int> y) {return get<1>(x) < get<1>(y);});

    for (int i = 0; i < n; i++){

        int index = get<2>(B[i]);
        
        if (i != 0){
            int prev_index = get<2>(B[i-1]);
            pair<int, int> cur = A[index];  
            pair<int, int> prev = A[prev_index];
            int dist = cur.second - prev.second;
            G[index].push_back(make_pair(dist, prev_index));
        }
        if (i!= n-1){
            int next_index = get<2>(B[i+1]);
            pair<int, int> cur = A[index];  
            pair<int, int> next = A[next_index];
            int dist = next.second - cur.second;
            G[index].push_back(make_pair(dist, next_index));
        }
    }

    // Dijkstra 
    int tab[n];  
    for (int i = 0; i < n; i++)
        tab[i] = INT_MAX;

    priority_queue <para,std::vector<para>, std::greater<para>> Q; 
    Q.push(make_pair(0, 0)); 

    while (!Q.empty() && tab[n-1] == INT_MAX){
        pair<int, int> p = Q.top(); 
        Q.pop();    
        if (tab[p.second] < INT_MAX)
            continue;
        tab[p.second] = p.first; 
        pair<int, int> new_p;
        for(pair<int, int> i : G[p.second]){
            pair<int, int> new_p = i; 
            new_p.first += p.first; 
            Q.push(new_p); 
        }
    }
    cout<<tab[n-1]<<endl;  

}
