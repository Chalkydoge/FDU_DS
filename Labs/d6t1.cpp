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
    if(nums.front() == -1)
        return NULL;
    TreeNode *root = new TreeNode(nums.front());
    queue<TreeNode *> q;
    q.push(root);

    int i = 1;
    while((i < (int)nums.size()) & !q.empty()){
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


// t1 dfs(recursion)
bool dfs(TreeNode* root, int target){
    if(!root)
        return false;
    if(target == root->val && !root->left && !root->right)
        return true;
    int cur = target - root->val;
    return dfs(root->left, cur) || dfs(root->right, cur);
}

bool findPath(TreeNode* root, int target){
    if(!root)
        return false;
    return dfs(root, target);
}


int main(){
    int v, k;
    vector<int> nums;
    while(cin >> v){
        nums.push_back(v);
        if(cin.get() == '\n')
            break;
    }
    cin >> k;
    TreeNode *root = buildTree(nums);
    cout << boolalpha << findPath(root, k) << endl;

    return 0;
}
