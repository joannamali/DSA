// used: segment tree

#include <iostream> 
#include <algorithm>
#include <map>
#include <queue>
using namespace std; 

#define pair pair<int, int>
#define mp make_pair

vector<int> D;

void add_num(int t, int quantity){
    while (t != 0){
        D[t] += quantity; 
        t /= 2; 
    }
}

void add(int t){
    add_num(t, 1);
}

void remove(int t){
    add_num(t, -1);
}

int reach (int cur, int z1, int z2, int a, int b){
    if (b < z1 || a > z2)
        return 0; 

    if (a <= z1 && z2 <= b)
        return D[cur]; 
    
    return (reach(cur * 2, z1, (z1+z2)/2, a, b) + reach (cur * 2 + 1, (z1+z2)/2+1, z2, a, b));
}

int main(){
    int n, k; 
    cin>>n>>k; 
    int tab[n][3], t[n]; 
    priority_queue<pair,std::vector<pair>, std::greater<pair>> Qstart, Qend; 

    for (int i = 0; i < n; i++){
        cin>>tab[i][0]>>tab[i][1]>>tab[i][2]; 
        Qstart.push(mp(tab[i][0], tab[i][2])); 
        Qend.push(mp(tab[i][1], tab[i][2]));
        t[i] = tab[i][2]; 
    }
    sort(t, t + n);  
     
    map<int, int> T; 
    int nr = 0; 
    for (int i = 0; i < n; i++){
        if (i != 0 && t[i] != t[i-1])
            nr++; 
        T.insert(mp(t[i], nr)); 
    }

    int range[nr+1][2];
    int ost = 0;
    for(int i = 0; i < n; i++){
        while (t[i] - k > t[ost])
            ost++; 
        range[T[t[i]]][0] = T[t[ost]];  
        range[T[t[i]]][1] = T[t[i]];    
    }
    ost = n-1;
    for(int i = n-1; i >= 0; i--){
        while (t[i] + k < t[ost])
            ost--; 
        range[T[t[i]]][1] = T[t[ost]]; 
    }

    int d_size = 1; 
    while (d_size < nr + 1)
        d_size *= 2; 
    

    for (int i = 0; i <= d_size*2; i++)
        D.push_back(0); 

    int liscie = d_size; 
    long long suma = 0; 
    while (!Qstart.empty()){
        pair p;

        if (Qend.top().first < Qstart.top().first){
            p = Qend.top(); 
            Qend.pop(); 
            remove(liscie + T[p.second]); 
        }
        else {
            p = Qstart.top(); 
            Qstart.pop(); 
            suma += reach(1, 0, liscie-1, range[T[p.second]][0], range[T[p.second]][1]); 
            add(liscie + T[p.second]); 
        }            
    }

    cout<<suma<<endl; 
}
