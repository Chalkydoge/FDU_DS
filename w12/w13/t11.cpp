#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <set>
#define MAXN 100
#define INF 0x3f3f3f3f
#define PII pair<int, int>
using namespace std;

int N;

struct edge{
    int from, to;
    int weight;
    edge(int a, int b, int c): from(a), to(b), weight(c){}
};

vector<vector<edge>> res;
vector<edge> mst;

void dfs(int cur, vector<int>& dist, vector<int>& pre, vector<edge>& mst, vector<int>& vis, int N, vector<vector<int>>& mat){
    vis[cur] = 1;

    int min_cost = INF;
    int next = -1;

    // 1. find nearest neighbor
    for (int j = 0; j < N; ++j){
        if(j == cur)
            continue;
        if(!vis[j] && dist[j] != INF && dist[j] < min_cost){
            min_cost = dist[j];
            next = j;
        }
    }

    // if all visited, return mst
    if(next == -1){
        res.push_back(mst);
        return;
    }

    // loop through all possible vertexes
    vector<int> tmp;
    for (int j = 0; j < N; ++j){
        if(!vis[j] && dist[j] == min_cost){
            tmp.push_back(j);
        }
    }

    // dfs through all vertexes, find possible mst(s)
    for(int next: tmp){
        vector<int> dist_k(dist.begin(), dist.end());
        vector<int> vis_k(vis.begin(), vis.end());
        vector<edge> mst_k(mst.begin(), mst.end());
        vector<int> pre_k(pre.begin(), pre.end());

        // relax after adding vertex 'next'
        for (int k = 0; k < N; ++k){
           if(!vis_k[k] && mat[next][k] != 0 && dist_k[k] > mat[next][k]){
               dist_k[k] = mat[next][k];
               pre_k[k] = next;
            }
        }
        mst_k.push_back(edge(pre[next], next, dist[next]));
        dfs(next, dist_k, pre_k, mst_k, vis_k, N, mat);
    }
}

void prim(int start, vector<edge>& mst, vector<vector<int>>& mat){
    // init of start
    vector<int> dist(N, INF);
    vector<int> vis(N, 0);
    vector<int> pre(N, 0);

    for (int i = 0; i < N; ++i){
        if(mat[start][i] != 0)
            dist[i] = mat[start][i];
    }

    dist[start] = 0;
    dfs(start, dist, pre, mst, vis, N, mat);
}

void print(){
    for(auto& mst: res){
        for(edge& m: mst){
            cout << "(" << char('A' + m.from) << ", " << char('A' + m.to) << ", " << m.weight << ") ";
        }
        cout << endl;
    }

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

    char d;
    cin >> d;

    char c = 'A';
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
            return a.weight < b.weight;
        });
    }

    for (int i = 0; i < N; ++i){
        cout << char(c + i) << ": ";
        for (auto e : adj[i]){
            cout << char(c + e.to) << ' ';
        }
        cout << endl;
    }

    prim(0, mst, mat);
    print();
    return 0;
}
