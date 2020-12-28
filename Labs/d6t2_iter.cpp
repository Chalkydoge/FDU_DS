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


// t2 non-recursion
vector<double> get_average(TreeNode* root){
    queue<TreeNode *> q;
    q.push(root);
    vector<double> res;

    while(!q.empty()){
        int sz = (int)q.size();
        double level_sum = 0.0;
        int tmp = sz;
        while(sz--){
            TreeNode *t = q.front();
            q.pop();
            level_sum += t->val;
            if(t->left)
                q.push(t->left);
            if(t->right)
                q.push(t->right);
        }
        res.push_back(level_sum / tmp);
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
    vector<double> res = get_average(root);
    for (int i = 0; i < (int)res.size(); ++i){
        cout << res[i] << " ";
    }
    return 0;
}
