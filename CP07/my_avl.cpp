#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;


struct TreeNode{
    int val;
    int height;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), height(0), left(nullptr), right(nullptr){}
};


class AVL_Tree{
    private:
        TreeNode *root;
        int size;

        int get_height(TreeNode *);
        int get_balance_factor(TreeNode*);
        TreeNode* rotate_right(TreeNode*);
        TreeNode* rotate_left(TreeNode*);
        TreeNode* re_balance(TreeNode *);
        TreeNode* insert(TreeNode* t, const int val);
        TreeNode* erase(TreeNode *&, const int);
        TreeNode* get_min(TreeNode *);
        void dfs(TreeNode *);

    public:
        AVL_Tree() {
            root = nullptr;
            size = 0;
        }
        AVL_Tree(vector<int> &nums);
        ~AVL_Tree();
        int get_height() { return get_height(root); }
        int get_balance_factor() { return get_balance_factor(root); }
        void insert(const int val) {
            this->root = insert(this->root, val);
            ++size;
        }
        void erase(const int val) { erase(this->root, val); }
        void bfs();
        const int get_size() { return size; }
};

AVL_Tree::~AVL_Tree(){
    dfs(this->root);
}

void AVL_Tree::dfs(TreeNode* root){
    if(!root)
        return;
    dfs(root->left);
    dfs(root->right);
    delete root;
}

/*  TODO      Get height of a certain node
*
*   input(s): The pointer to the node
*
*   output(s): The height of the node
*/
int AVL_Tree::get_height(TreeNode* root){
    if(!root)
        return -1;
    else
        return max(get_height(root->left), get_height(root->right)) + 1;
}

/*  TODO      Calculate factor by heights
*
*   input(s): The pointer to the node
*
*   output(s): The balance factor of the node
*/
int AVL_Tree::get_balance_factor(TreeNode* root){
    if(!root)
        return 0;
    else
        return get_height(root->right) - get_height(root->left);
}


/*  TODO      rotate right
*
*   input(s): the root of tree
*
*   output(s): the rotated tree's root
*/
TreeNode* AVL_Tree::rotate_right(TreeNode* root){
    TreeNode *cur_left = root->left;
    /*      /           /\
    *      /   =>      /  \
    *     /
    */
    root->left = cur_left->right;
    cur_left->right = root;

    // update the modified heights!
    cur_left->height = max(get_height(cur_left->left), get_height(cur_left->right)) + 1;
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    return cur_left;
}


/*  TODO      rotate left
*
*   input(s): the root of tree
*
*   output(s): the rotated tree's root
*/
TreeNode* AVL_Tree::rotate_left(TreeNode* root){
    TreeNode *cur_right = root->right;
    /*      \             /\
    *        \   =>      /  \
    *         \
    *
    */
    root->right = cur_right->left;
    cur_right->left = root;

    // update the modified heights!
    cur_right->height = max(get_height(cur_right->left), get_height(cur_right->right)) + 1;
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    return cur_right;
}


/*  TODO      rebalance whole tree
*
*   input(s): the root of tree
*
*   output(s): the balanced tree's root
*/
TreeNode* AVL_Tree::re_balance(TreeNode* root){
    int fact = get_balance_factor(root);
    // cout << fact << endl;
    int lean_right = get_balance_factor(root->right);
    int lean_left = get_balance_factor(root->left);

    if(fact > 1 && lean_right > 0){ // 1. RR
        return rotate_left(root);
    }
    else if(fact > 1 && lean_right <= 0){ // 2. RL
        TreeNode *tmp = rotate_right(root->right);
        root->right = tmp;
        return rotate_left(root);
    }
    else if (fact < -1 && lean_left < 0){ // 3. LL
        return rotate_right(root);
    }
    else if(fact < -1 && lean_left >= 0){ // 4. LR
        TreeNode *tmp = rotate_left(root->left);
        root->left = tmp;
        return rotate_right(root);
    }
    else{ // 5. Normal
        // root->height = 1 + max(get_height(root->left), get_height(root->right));
        return root;
    }
}


/*  TODO      Insert node of 'val' into AVL-tree
*
*   input(s): The root ptr && the value of the node
*
*   output(s): None
*/
TreeNode* AVL_Tree::insert(TreeNode* root, const int val){
    // cout << boolalpha << (root == nullptr) << endl;
    if(!root){
        TreeNode* n = new TreeNode(val);
        return n;
    }
    else if(root->val == val){
        return root;
    }
    else{
        if(root->val < val){
            root->right = insert(root->right, val);
        }
        else{
            root->left = insert(root->left, val);
        }
    }
    root->height = 1 + max(get_height(root->left), get_height(root->right));
    return re_balance(root);
}

/*  TODO      Erase node of 'val' from AVL-tree
*
*   input(s): The root ptr && the value of the node
*
*   output(s): None
*/
TreeNode* AVL_Tree::erase(TreeNode* &root, const int val){
    if(!root)
        return nullptr;
    if(val > root->val)
        return erase(root->right, val);
    else if (val < root->val)
        return erase(root->left, val);
    else{
        if (!root->left || !root->right){
            --size;
            TreeNode *sub = nullptr;
            if(!root->left)
                sub = root->right;
            else
                sub = root->left;

            if(!sub)
                root = nullptr;
            else
                root = sub;
        }
        else{
            // CASE 4: The node has two subtrees
            TreeNode *tmp = get_min(root->right);
            root->val = tmp->val;
            cout << "The subtitute value for: " << root->val << endl;
            return erase(root->right, tmp->val);
        }
    }
    if(!root)
        return nullptr;

    root->height = 1 + max(get_height(root->left), get_height(root->right));
    return re_balance(root);
}

/*  TODO      Get minimum 'value' from AVL-tree
*
*   input(s): The root ptr
*
*   output(s): The min-value
*/
TreeNode* AVL_Tree::get_min(TreeNode* root){
    while(root->left){
        root = root->left;
    }
    return root;
}


void AVL_Tree::bfs(){
    queue<TreeNode *> q;
    q.push(this->root);
    while(!q.empty()){
        TreeNode *t = q.front();
        q.pop();
        cout << "Info:" << '\t' << t->val << '\t' << t->height << '\t' << endl;
        if(t->left)
            q.push(t->left);
        if(t->right)
            q.push(t->right);
    }
}

int main(){
    AVL_Tree my_tree;
    my_tree.insert(5);
    my_tree.insert(2);
    my_tree.insert(3);
    my_tree.insert(1);
    my_tree.insert(4);
    my_tree.insert(7);
    my_tree.insert(6);

    cout << my_tree.get_size() << endl;
    my_tree.bfs();

    my_tree.erase(5);
    cout << my_tree.get_size() << endl;
    my_tree.bfs();
    return 0;
}
