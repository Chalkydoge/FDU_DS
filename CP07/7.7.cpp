#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left = NULL;
    TreeNode *right = NULL;
    TreeNode(int v) : val(v), left(NULL), right(NULL){}
};

void bfs(TreeNode* root){
    queue<TreeNode *> q;
    q.push(root);
    while(!q.empty()){
        TreeNode *x = q.front();
        cout << x->val << '\t';
        q.pop();
        if(x->left)
            q.push(x->left);
        if(x->right)
            q.push(x->right);
    }
}

void mid_order(TreeNode* root){
    if(!root)
        return;
    mid_order(root->left);
    cout << root->val << ' ';
    mid_order(root->right);
}

TreeNode* build(vector<int>& nums){
    int i = 0;
    TreeNode* root = new TreeNode(nums[i]);
    ++i;
    int n = nums.size();
    queue<TreeNode *> q;
    q.push(root);

    while((i < n) & !q.empty()){
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

long long pre_val = LONG_LONG_MIN;

inline void reset(){
    pre_val = LONG_LONG_MIN;
}

bool is_BST(TreeNode* root){
    if(!root)
        return true;
    if(!is_BST(root->left)){
        return false;
    }
    if(root->val < pre_val){
        return false;
    }
    pre_val = root->val;
    return is_BST(root->right);
}

TreeNode* insert(TreeNode* root, int target){
    if(!root)
        return new TreeNode(target);
    if(root->val > target){
        root->left = insert(root->left, target);
    }
    else if(root->val < target){
        root->right = insert(root->right, target);
    }
    else{
        root->val = target;
    }
    return root;
}

TreeNode* merge_two_BST(TreeNode* r1, TreeNode* r2){
    // r1 as basic(larger size)
    // r2 is smaller than 'r1'

    stack<TreeNode *> stk;
    TreeNode *cur = r2;

    while(!stk.empty() || cur){
        while(cur){
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        // cout << cur->val << ' ';

        // TODO: insert node into r1
        insert(r1, cur->val);
        cur = cur->right;
    }

    return r1;
}

int main(){
    vector<int> notBST = {1, 1, 4, 5, 1, 4, -1};
    vector<int> isBST1 = {4, 2, 7, 1, 3, 6, 8};
    vector<int> isBST2 = {11, 9, 15};

    TreeNode *root = build(notBST);
    cout << boolalpha << is_BST(root) << endl;
    reset();
    TreeNode *root2 = build(isBST1);
    cout << boolalpha << is_BST(root2) << endl;

    TreeNode *root3 = build(isBST2);
    root2 = merge_two_BST(root2, root3);
    mid_order(root2);
    return 0;
}
