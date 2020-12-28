#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

vector<string> res;
vector<string> in_ord;

struct TreeNode{
    char data;
    TreeNode* left, *right;
    TreeNode(char c) : data(c), left(NULL), right(NULL){}
};

inline bool cmp(char a, char b){
    int va = a - '0';
    int vb = b - '0';
    return va > vb;
}

TreeNode* insert(TreeNode* root, char c){
    if(!root){
        root = new TreeNode(c);
        return root;
    }
    else if(cmp(root->data, c)){ // c <= root->val
        root->left = insert(root->left, c);
    }
    else{
        root->right = insert(root->right, c);
    }
    return root;
}

bool is_same_tree(TreeNode* l1, TreeNode* l2){
    if(!l1 && !l2){
        return true;
    }
    if(!l1 || !l2)
        return false;
    if(l1->data != l2->data)
        return false;
    return is_same_tree(l1->left, l2->left) && is_same_tree(l1->right, l2->right);
}

void pre_trav(TreeNode* r, const int idx){
    if(!r)
        return;
    res[idx] += r->data;
    pre_trav(r->left, idx);
    pre_trav(r->right, idx);
}

void in_trav(TreeNode* r, const int idx){
    if(!r)
        return;
    in_trav(r->left, idx);
    in_ord[idx] += r->data;
    in_trav(r->right, idx);
}

int main(){
    int N;
    cin >> N;
    res.clear();
    res.resize(N + 1, "");
    in_ord.clear();
    in_ord.resize(N + 1, "");

    vector<string> tmp;
    for (int i = 0; i <= N; ++i){
        string str;
        cin >> str;
        tmp.push_back(str);
    }
    string s;
    cin >> s;

    TreeNode *cur_root = NULL;
    for(char c : tmp[0]){
        cur_root = insert(cur_root, c);
    }
    pre_trav(cur_root, 0);

    for (int i = 1; i <= N; ++i){
        TreeNode *tmp_root = NULL;
        for(char c : tmp[i]){
            tmp_root = insert(tmp_root, c);
        }
        pre_trav(tmp_root, i);

        if(res[0] == res[i]){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }

    return 0;
}
