#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

struct edge{
    int from, to;
    int w;
    edge(int a = 0, int b = 0, int c = 0):from(a), to(b), w(c){}
};

struct cmp{
    bool operator()(edge & a, edge & b){
        return a.w > b.w;
    }
};

vector<vector<edge>> prim_res;
int MST_weight = 0;
int N = 0;
int M = 0;

void dfs(vector<vector<edge>>& adj, int N, priority_queue<edge, vector<edge>, cmp>& pq, vector<int>& vis, vector<edge>& mst){
    if((int)mst.size() == N - 1){
        prim_res.push_back(mst);
        return;
    }

    while(!pq.empty()){
        // cout << "visited" << endl;
        int f = pq.top().from, t = pq.top().to;
        int w = pq.top().w;
        if(vis[f] && vis[t]){
            pq.pop();
            continue;
        }
        else{
            vector<edge> possible_edge;
            while(!pq.empty() && pq.top().w == w){
                possible_edge.push_back(pq.top());
                pq.pop();
            } // get all min-weight edges

            for(auto e: possible_edge){
                int from = e.from, to = e.to;
                mst.push_back(e); // temp res for possible trees
                if(!vis[from]){
                    vis[from] = 1;
                    priority_queue<edge, vector<edge>, cmp> pq1 = pq;
                    vector<int> vis1(vis.begin(), vis.end());
                    vector<edge> mst1(mst.begin(), mst.end());
                    for(auto e: adj[from]){
                        pq1.push(e);
                    }
                    dfs(adj, N, pq1, vis1, mst1);
                }
                if(!vis[to]){
                    vis[to] = 1;
                    priority_queue<edge, vector<edge>, cmp> pq2 = pq;
                    vector<int> vis2(vis.begin(), vis.end());
                    vector<edge> mst2(mst.begin(), mst.end());
                    for(auto e: adj[to]){
                        pq2.push(e);
                    }
                    dfs(adj, N, pq2, vis2, mst2);
                }
            }
        }
    }
}

void prim(vector<vector<edge>>& adj, char d, int N, int& MST_weight){
    vector<edge> mst;
    vector<int> vis(N, 0);
    int start = d - 'A';

    vis[start] = 1;
    priority_queue<edge, vector<edge>, cmp> pq;
    for(auto e : adj[start]){
        pq.push(e);
    }

    dfs(adj, N, pq, vis, mst);
}

int main(){
    cin >> N;
    vector<vector<int>> mat(N, vector<int>(N, 0));

    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            int v;
            cin >> v;
            mat[i][j] = v;
        }
    }

    char c, d;
    c = 'A';
    cin >> d;


    vector<vector<edge>> adj(N, vector<edge>());
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            if(mat[i][j] != 0){
                adj[i].push_back(edge(i, j, mat[i][j]));
            }
        }
    }

    for (int i = 0; i < N; ++i){
        sort(adj[i].begin(), adj[i].end(), [](edge &a, edge &b) {
            return a.w < b.w;
        });
    }

    for (int i = 0; i < N; ++i){
        cout << char(c + i) << ": ";
        for (auto e : adj[i]){
            cout << char(c + e.to) << ' ';
        }
        cout << endl;
    }


    prim(adj, d, N, MST_weight);

    for(auto prim: prim_res){
        for(auto w: prim){
            cout << '(' << char('A' + w.from) << ',' << char(w.to + 'A') << ',' << w.w << ')' << ' ';
        }
        cout << endl;
    }

    return 0;
}
