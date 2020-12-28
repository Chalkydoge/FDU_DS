#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

int dp[205];
struct node{
    int floor;
    int step;
    node(int a, int b) : floor(a), step(b){}
};

// 2. 非递归方式求解
int main(){
    vector<int> nums;
    int N, S, E;
    cin >> N >> S >> E;

    for (int i = 0; i < N; ++i){
        int o;
        cin >> o;
        nums.push_back(o);
    }

    for (int i = 0; i < 205; ++i){
        dp[i] = 205;
    }

    stack<node> q;
    q.push(node(S, 0));

    dp[S] = 0;

    while(!q.empty()){
        node x = q.top();
        q.pop();
        int up = x.floor + nums[x.floor - 1];
        int down = x.floor - nums[x.floor - 1];
        // cout << x.floor << endl;
        if(up <= N){
            int tmp = x.step + 1;
            if(dp[up] > tmp){
                dp[up] = tmp;
                q.push(node(up, tmp));
            }
        }
        if(down >= 1){
            int tmp = x.step + 1;
            if(dp[down] > tmp){
                dp[down] = tmp;
                q.push(node(down, tmp));
            }
        }
    }

    if(dp[E] == 205){
        cout << -1 << endl;
    }
    else{
        cout << dp[E] << endl;
    }
    return 0;
}
