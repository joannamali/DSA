#include<iostream>
#include<string>
using namespace std;

int main(){
    string s; 
    cin>>s; 
    int minimum = s.size(), count = 0;  
    char current = s[0];
    for (char c : s){
        if (c == '*')
            count++; 
        else if (c == current)
            count = 1;
         else {
            if (current != '*')
                minimum = min(minimum, count); 
            current = c;
            count = 1; 
        }
    }
 
    cout<<s.size()-minimum+1<<endl;       
}
