#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

struct TreeNode{
    int weight;
    int left, right;
    int height = 0;
    TreeNode(int w = 0, int l = -1, int r = -1) : weight(w), left(l), right(r){}
};

TreeNode tr[105];
int fa[105];

int get_height(int root){
    if(tr[root].left == -1 && tr[root].right == -1)
        return tr[root].height = 0;
    else if(tr[root].left == -1){
        return tr[root].height = get_height(tr[root].right) + 1;
    }
    else if(tr[root].right == -1){
        return tr[root].height = get_height(tr[root].left) + 1;
    }
    else{
        return tr[root].height = (1 + max(get_height(tr[root].left), get_height(tr[root].right)));
    }
}

bool dfs(int idx){
    if(tr[idx].left == -1 && tr[idx].right == -1){
        return true;
    }

    int diff = (tr[tr[idx].left].height - tr[tr[idx].right].height);
    bool flag = (diff <= 1) && (diff >= -1);
    return dfs(tr[idx].left) && dfs(tr[idx].right) && (flag);
}

int main(){
    for (int j = 0; j < 105; ++j){
        fa[j] = -1;
    }
    int N;
    cin >> N;

    vector<int> nums;
    for (int i = 0; i < N; ++i){
        int v;
        cin >> v;
        tr[i + 1] = TreeNode(v);
    }

    for (int i = 0; i < N; ++i){
        string s1, s2;
        cin >> s1 >> s2;
        if(s1 == "-" && s2 == "-"){
            continue;
        }
        else if(s1 == "-"){
            int node = stoi(s2);
            fa[node] = i + 1;
            tr[i + 1].right = node;
        }
        else if(s2 == "-"){
            int node = stoi(s1);
            fa[node] = i + 1;
            tr[i + 1].left = node;
        }
        else{
            int l = stoi(s1), r = stoi(s2);
            fa[l] = i + 1;
            fa[r] = i + 1;
            tr[i + 1].left = l;
            tr[i + 1].right = r;
        }
    }

    int root = 1;
    for (int i = 1; i <= N; ++i){
        if(fa[i] == -1){
            root = i;
            break;
        }
    }

    get_height(root);
    bool res = dfs(root);
    if(res)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
