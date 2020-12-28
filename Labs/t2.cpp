#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct node{
    int floor;
    int step;
    node(int a, int b) : floor(a), step(b){}
};

int dp[205];
int nums[205];
int N, S, E;

// 1. 递归方式求解
void dfs(int x, int step){
    int up = x + nums[x];
    int down = x - nums[x];
    if(up <= N){
        int r = step + 1;
        if(dp[up] >= r){
            dp[up] = r;
            dfs(up, r);
        }
    }
    if(down >= 0){
        int r = step + 1;
        if(dp[down] > r){
            dp[down] = r;
            dfs(down, r);
        }
    }
}

int main(){
    for (int i = 0; i < 205; ++i){
        dp[i] = 205;
    }

    cin >> N >> S >> E;
    for (int i = 0; i < N; ++i){
        int o;
        cin >> o;
        nums[i + 1] = o;
    }

    dfs(S, 0);
    if(dp[E] == 205){
        cout << -1 << endl;
    }
    else{
        cout << dp[E] << endl;
    }
    return 0;
}
