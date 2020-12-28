#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

int vis[100];
vector<int> edge[100];
stack<int> st;

int path[100];

void dfs(int x){
    st.push(x);
    vis[x] = 1;
    while(!st.empty()){
        int tmp = st.top();
        st.pop();
        cout << "visited node: " << tmp << endl;
        for(int y : edge[tmp]){
            if(!vis[y]){
                vis[y] = 1;
                st.push(y);
            }
        }
    }
}


int main(){
    for (int i = 0; i < 100; ++i)
        vis[i] = 0;
    edge[0].push_back(1);
    edge[0].push_back(2);
    edge[1].push_back(2);
    edge[2].push_back(3);
    edge[2].push_back(0);
    dfs(0);
    return 0;
}
