#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;

int fa[10000];
int sz[10000];
int CC = 0;

int get_fa(int x){
    while(x != fa[x]){
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

void u(int x, int y){
    int ra = get_fa(x);
    int rb = get_fa(y);

    if(ra == rb)
        return;
    else{
        if(sz[ra] >= sz[rb]){
            sz[ra] += sz[rb];
            fa[rb] = ra;
        }
        else{
            sz[rb] += sz[ra];
            fa[ra] = rb;
        }
        --CC;
    }
}

bool c(int x, int y){
    return get_fa(x) == get_fa(y);
}

void init(int n){
    for (int i = 0; i < n; ++i){
        fa[i] = i;
        sz[i] = 1;
    }
    CC = n;
}

// // TEST1
// 3
// 1 1 0
// 0 1 1
// 0 1 1
//
// # output = 3


// // TEST2
// 4
// 1 0 0 1
// 0 1 1 0
// 0 1 1 0
// 1 0 0 1
//
// # output = 2

// // TEST3
// 5
// 1 0 0 0 1
// 0 1 0 1 0
// 1 0 1 0 1
// 0 1 0 1 0
// 1 0 0 0 1
//
// # output = 3


int main(){
    int N;
    cin >> N;
    init(N);

    vector<vector<int>> mat(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            int v;
            cin >> v;
            mat[i][j] = v;
            if(mat[i][j] != 0){
                u(i, j);
            }
        }
    }

    int res = -1;
    for (int i = 0; i < N; ++i){
        res = max(res, sz[i]);
    }
    cout << res << endl;
    return 0;
}
