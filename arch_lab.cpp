#include <iostream>
#include <utility>
#include <map>
#define PII pair<int, int>

using namespace std;
const int MAXN = 1000;

map<PII, int> dp;
/*  considering the process of seraching in 0 - 9
*   考虑跳转过程中的比较次数优化
*     je == 1'
*      jl <  2'
*    >  3'
*
*   PII ij,  dp = ([i, j], count)
*/

int dfs(PII ij){
    if(ij.first >= ij.second)
        return 0;
    if(dp.count(ij))
        return dp[ij];

    int l, r;
    tie(l, r) = ij;
    PII res(MAXN, MAXN);

    for (int m = l; m <= r; ++m){
        int sum = 2;    // test, je, 2 instr

        if(l <= m - 1){ // LEFT_BRANCH
            sum += (l < m - 1) + (m - l) + dfs(make_pair(l, m - 1));
        }
        if(m + 1 <= r){ // RIGHT_BRANCH
            sum += (m + 1 < r) + (r - m) + dfs(make_pair(m + 1, r));
        }

        res = min(res, make_pair(sum, m));
    }
    cout << "l = " << l << ", r = " << r << ", critical_point = " << res.second << ", instr_count: " << res.first << endl;
    return dp[ij] = res.first;
}

int main(){
    int l = 0, r = 9;
    int res = dfs(make_pair(l, r));
    return 0;
}

// critical points are: 1, 3, 4, 6, 8
//              [0, 9]
//            /    |    \
//         [0, 2]  3    [4, 9]
//       /  |  \        /   |  \
//      0   1   2    [4, 6] 7  [8, 9]
//                   / | \      /  \
//                  4  5  6     8   9
