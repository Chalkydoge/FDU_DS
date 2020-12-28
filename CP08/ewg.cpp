#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <queue>
using namespace std;

#define MAXN 100
#define MAXINT 10000
#define PII pair<int, int>
int mat[MAXN][MAXN];
int S[MAXN];
int distTo[MAXN];
int dp[MAXN][MAXN];
int path[MAXN];

void init(){
    for (int i = 0; i < MAXN; ++i){
        S[i] = 0;
    }
    for (int i = 0; i < MAXN; ++i){
        distTo[i] = MAXINT;
    }
    for (int i = 0; i < MAXN; ++i){
        path[i] = 0;
    }
}

void floyd_SP(int N){
    init();

    for (int k = 1; k <= N; ++k){
        for (int i = 1; i <= N; ++i){
            for (int j = 1; j <= N; ++j){
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }
}

void SP(int N, int start){
    init();
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    distTo[start] = 0;
    path[start] = 0;
    pq.push(make_pair(0, start));

    while(!pq.empty()){
        auto p = pq.top();
        pq.pop();
        int path_len = p.first, from = p.second;
        if(distTo[from] < path_len)
            continue;
        for (int i = 1; i <= N; ++i){
            if(distTo[i] > mat[from][i] + path_len){
                distTo[i] = path_len + mat[from][i];
                path[i] = start;
                pq.push(make_pair(distTo[i], i));
            }
        }
    }
}

void shortestPath(int N, int start){
    for (int i = 1; i <= N; ++i){
        S[i] = 0;
        distTo[i] = mat[start][i];
        path[i] = 0;
        if(distTo[i] < MAXINT){
            path[i] = start;
        }
    }

    path[start] = 0;
    S[start] = 1;
    distTo[start] = 0;

    int MinDist, next;
    for (int i = 1; i <= N; ++i){
        MinDist = MAXINT;
        next = 0;
        for (int j = 1; j <= N; ++j){
            if(S[j] == 0){
                if(distTo[j] < MinDist){
                    MinDist = distTo[j];
                    next = j;
                }
            }
        }

        if(next == 0)
            continue;
        else{
            S[next] = 1;
            for (int j = 1; j <= N; ++j){
                if(S[j] == 0 && mat[next][j] < MAXINT){
                    if(distTo[next] + mat[next][j] < distTo[j]){
                        distTo[j] = distTo[next] + mat[next][j];
                        path[j] = next;
                    }
                }
            }
        }
    }
}

void show(int N){
    for (int i = 1; i <= N; ++i){
        cout << "The cost from start to " << i << " is: " << distTo[i] << endl;
    }
}

vector<int> NewPath(int N, int start, int end){
    vector<int> res;
    stack<int> stk;
    while(end != 0){
        stk.push(end);
        end = path[end];

    }

    while(!stk.empty()){
        res.push_back(stk.top());
        stk.pop();
    }

    int n = (int)res.size();
    for (int i = 0; i < n; ++i){
        if(i != n - 1){
            cout << res[i] << "->";
        }
        else{
            cout << res[i] << endl;
        }
    }
    return res;
}

int main(){
    ifstream input("test.txt");
    int N;
    input >> N;
    cout << N << endl;

    for (int i = 1; i <= N; ++i){
        for (int j = 1; j <= N; ++j){
            int v;
            input >> v;
            if(v == 0){
                mat[i][j] = MAXINT;
            }
            else{
                mat[i][j] = v;
            }
        }
    }

    input.close();

    int start = 1;
    // int end = 4;

    SP(N, start);
    show(N);

    init();
    shortestPath(N, start);
    show(N);

    // NewPath(N, start, end);
    return 0;
}
