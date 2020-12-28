#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(NULL), right(NULL){}
};


TreeNode* buildTree(vector<int>& nums){
    if(nums.size() == 0)
        return NULL;
    TreeNode *root = new TreeNode(nums.front());
    queue<TreeNode *> q;
    q.push(root);

    int i = 1;
    while(!q.empty() && (i < (int)nums.size())){
        TreeNode *node = q.front();
        q.pop();
        if(node){
            TreeNode *lc = (nums[i] != -1) ? new TreeNode(nums[i]) : NULL;
            TreeNode *rc = (i + 1 < (int)nums.size() && nums[i + 1] != -1) ? new TreeNode(nums[i + 1]) : NULL;
            node->left = lc;
            node->right = rc;
            q.push(lc);
            q.push(rc);
            i += 2;
        }
    }
    return root;
}

void pre_trav(TreeNode* root){
    stack<TreeNode *> st;
    while(root || !st.empty()){
        if(root){
            cout << root->val << " ";
            st.push(root);
            root = root->left;
        }
        else{
            root = st.top();
            st.pop();
            root = root->right;
        }
    }
}

void trav(TreeNode* root){
    if(!root)
        return;
    cout << root->val << endl;
    trav(root->left);
    trav(root->right);
}

// t2-recursion
void dfs(TreeNode* root, int level, vector<int>& level_sums, vector<int>& cnt){
    if(!root)
        return;
    if(level < (int)level_sums.size()){
        level_sums[level] += root->val;
        ++cnt[level];
    }
    else{
        level_sums.push_back(root->val);
        cnt.push_back(1);
    }
    dfs(root->left, level + 1, level_sums, cnt);
    dfs(root->right, level + 1, level_sums, cnt);
}

vector<double> get_averageII(TreeNode* root){
    vector<int> level_sums, cnt;
    dfs(root, 0, level_sums, cnt);

    vector<double> res;
    for (int i = 0; i < (int)level_sums.size(); ++i){
        res.push_back((double)level_sums[i] / cnt[i]);
    }
    return res;
}

int main(){
    int v;
    vector<int> nums;
    while(cin >> v){
        nums.push_back(v);
        if(cin.get() == '\n')
            break;
    }

    TreeNode *root = buildTree(nums);
    // trav(root);
    vector<double> res = get_averageII(root);
    for (int i = 0; i < (int)res.size(); ++i){
        cout << res[i] << " ";
    }
    return 0;
}
