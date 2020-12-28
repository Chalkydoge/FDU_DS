#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Node{
    int data;
    Node *lchild, *rchild;
    int ltag, rtag;
    Node(int n = -1) : data(n), lchild(NULL), rchild(NULL), ltag(0), rtag(0){}
};


Node* create_thread_tree(vector<int>& a, int n){

}

void thread_sort(vector<int>& a, int n){
    Node* head;
    head = create_thread_tree(a, n);
    midorder(head);
}

int main(){
    int n;
    vector<int> a;
    cin >> n;
    for(int i = 0; i < n; ++i){
        int t;
        cin >> t;
        a.push_back(t);
    }
    thread_sort(a, n);
    return 0;
}
