#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct BinNode{
    int val;
    int ltag, rtag;
    BinNode *left;
    BinNode *right;
    BinNode(int v) : val(v), ltag(0), rtag(0), left(nullptr), right(nullptr){}
};

void pre_thread(BinNode* t, BinNode* &pre){
    if(t){
        cout << t->val << endl;
        if(!t->left){
            t->ltag = 1;
            t->left = pre;
        }
        if(pre && !pre->right){
            pre->rtag = 1;
            pre->right = t;
        }
        pre = t;
        if(t->ltag != 1){
            pre_thread(t->left, pre);
        }
        if(t->rtag != 1){
            pre_thread(t->right, pre);
        }
    }
}

BinNode* succ_pre(BinNode* t){
    if(t->rtag == 1 || !t->right)
        return t->right;
    if(t->left)
        return t->left;
    else
        return nullptr;
}

BinNode* build(vector<int>& nums){
    int i = 0;
    BinNode* root = new BinNode(nums[i]);
    ++i;
    int n = nums.size();
    queue<BinNode *> q;
    q.push(root);

    while((i < n) & !q.empty()){
        BinNode *node = q.front();
        q.pop();
        if(node){
            BinNode *lc = (nums[i] != -1) ? new BinNode(nums[i]) : NULL;
            BinNode *rc = (i + 1 < (int)nums.size() && nums[i + 1] != -1) ? new BinNode(nums[i + 1]) : NULL;
            node->left = lc;
            node->right = rc;
            q.push(lc);
            q.push(rc);
            i += 2;
        }
    }

    return root;
}

void mid_thread(BinNode* t, BinNode* &pre){
    if(t){
        if(t->ltag == 0)
            mid_thread(t->left, pre);
        if(!t->left){
            t->left = pre;
            t->ltag = 1;
        }
        if(pre && !pre->right){
            pre->right = t;
            pre->rtag = 1;
        }
        pre = t;
        if(t->rtag == 0)
            mid_thread(t->right, pre);
    }
}

BinNode* first_mid(BinNode* t){
    while(t && t->ltag == 0){
        t = t->left;
    }
    return t;
}

BinNode* succ_mid(BinNode* t){
    if(t->rtag == 1){
        return t->right;
    }
    t = t->right;
    while(t && t->ltag == 0){
        t = t->left;
    }
    return t;
}

void mid_trav(BinNode* root){
    for (BinNode *s = first_mid(root); s; s = succ_mid(s)){
        cout << s->val << endl;
    }
}

void post_thread(BinNode* t, BinNode* &pre){
    if(t){
        if(t->ltag == 0)
            post_thread(t->left, pre);
        if(t->rtag == 0)
            post_thread(t->right, pre);
        // cout << t->val << endl;
        if(!t->left){
            t->left = pre;
            t->ltag = 1;
        }
        if(pre && !pre->right){
            pre->right = t;
            pre->rtag = 1;
        }
        pre = t;
    }
}

BinNode* first_post(BinNode* t){
    while(t && t->ltag == 0){
        t = t->left;
    }
    while(t->rtag == 0){
        t = t->right;
    }
    return t;
}

BinNode* find_parent(BinNode *p, BinNode* t){
    if(!t || !p || p == t){
        return nullptr;
    }
    if((p->ltag == 0 && p->left == t) || (p->rtag == 0 && p->right == t)){
        return p;
    }
    BinNode *s = nullptr;
    if(p->ltag == 0)
        s = find_parent(p->left, t);
    if(!s && p->rtag == 0){
        s = find_parent(p->right, t);
    }
    return s;
}

BinNode* succ_post(BinNode* root, BinNode* t){
    if(!t)
        return nullptr;
    if(t->rtag == 1)
        return t->right;
    else{
        BinNode *p = find_parent(root, t);
        if(p == root){
            if(p->left == t)
                return first_post(p->right);
            else
                return p;
        }
        else{
            return p;
        }
    }
}

void post_trav(BinNode* root){
    for (BinNode *s = first_post(root); s; s = succ_post(root, s)){
        cout << s->val << endl;
    }
}

vector<int> res;
int get_depth(BinNode* root){
    if(!root)
        return -1;
    return 1 + max(get_depth(root->left), get_depth(root->right));
}

void longestPath(BinNode* root){
    if(!root)
        return;
    res.push_back(root->val);
    int l = get_depth(root->left), r = get_depth(root->right);
    if(l >= r)
        return longestPath(root->left);
    else
        return longestPath(root->right);
}

int main(){
    vector<int> nums = {1, 2, 3, 4, 5, -1, -1};
    BinNode *root = build(nums);
    BinNode *pre = nullptr;
    longestPath(root);
    for(int i : res)
        cout << i << "->";
    cout << endl;
    // post_thread(root, pre);
    // post_trav(root);
    mid_thread(root, pre);
    mid_trav(root);
    BinNode* cur = find_parent(root, root->left->left);
    cout << cur->val << endl;
    return 0;
}
