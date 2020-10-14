#include <iostream>
using std::cout;
using std::endl;
using std::initializer_list;

template <typename T>
class SingleLinkList;

template <typename T>
class LinkList;

template <typename T>
class Node{
    friend class LinkList<T>;
    friend class SingleLinkList<T>;

    public:
        Node(const T& val) : data(val), next(nullptr) {}
        Node(const Node<T>& n) : data(n.data), next(n.next) {}
        Node<T> *insert_after(Node<T> *cur, const T &val);
        ~Node() {}

    private:
        T data;
        Node<T> *next;
};

template<typename T>
Node<T> * Node<T>::insert_after(Node<T> *cur, const T &val){
    if(!cur)
        return nullptr;
    Node<T> *new_node = new Node<T>(val);
    new_node->next = cur->next;
    cur->next = new_node;
    return new_node;
}

template<typename T>
class SingleLinkList{

public:
    SingleLinkList() { head = tail = nullptr; }
    SingleLinkList(const initializer_list<T> &ll);
    void convert2circular();
    void traverse();
    void dis_circular()
    {
        if (tail)
            tail->next = nullptr;
        return;
        }
    Node<T> *get_head() const { return head; }
    void set_head(Node<T> *h) { this->head = h; }
    void switch_neighbors();
    void reverse_k(const int &);
    Node<T>* reverse_int(Node<T> *, Node<T> *);

private:
    Node<T> *head, *tail;
    int size = 0;
};

template<typename T>
SingleLinkList<T>::SingleLinkList(const initializer_list<T>& ll){
    head = new Node<T>(*ll.begin());
    tail = head;
    ++size;
    for (auto it = ll.begin() + 1; it != ll.end(); ++it){
        tail->next =  new Node<T>(*it);
        tail = tail->next;
        ++size;
    }
    tail->next = nullptr;
}

// 2.19
template<typename T>
void SingleLinkList<T>::convert2circular(){
    int len = 0;
    Node<T>* p = head;
    while(p){
        p = p->next;
        ++len;
    }

    Node<T> *dummy_head = new Node<T>(len);
    dummy_head->next = head;
    head = dummy_head;
    tail->next = dummy_head;
}

template<typename T>
void SingleLinkList<T>::traverse(){
    Node<T>* p = head;
    while(p){
        if(p->next)
            cout << p->data << "->";
        else
            cout << p->data << endl;
        p = p->next;
    }
}

template <typename T>
class LinkList{

public:
    LinkList(){
        head = tail = new Node<T>(0);
        size = 0;
    }
    LinkList(const LinkList &);
    LinkList(const initializer_list<T> &ll);
    void append_node(const T &val);
    void traverse();
    void merge_lists(LinkList<T>&);
    void reverse_list();
    void make_circular(const int &pos);
    void dismake_circular(const int &pos);
    void delete_prev(const T &val);
    bool find_circle();
    Node<T> *get_head() const { return head; }

    ~LinkList(){
        Node<T> *p = head;
        while(p){
            Node<T> *q = p;
            p = p->next;
            // cout << "Node(s) whose value is: " << q->data << " has been deleted" << endl;
            delete q;
        }
    }
    void free(){
        Node<T> *p = head;
        while(p){
            Node<T> *q = p;
            p = p->next;
            cout << "Node(s) whose value is: " << q->data << " has been deleted" << endl;
            delete q;
        }
    }

private:
    Node<T> *reverse(Node<T> *head);
    Node<T> *head;
    Node<T> *tail;
    int size;
};

template <typename T>
LinkList<T>::LinkList(const initializer_list<T> &ll){
    head = tail = new Node<T>(0);
    size = 0;
    for (auto it = ll.begin(); it != ll.end(); ++it){
        append_node(*it);
    }
}

template <typename T>
void LinkList<T>::append_node(const T& val){
    tail = tail->insert_after(tail, val);
    tail->next = nullptr;
    ++size;
}

template <typename T>
void LinkList<T>::traverse(){
    Node<T> *p = head->next;
    while(p){
        if(p->next)
            cout << p->data << "->";
        else
            cout << p->data << endl;
        p = p->next;
    }
}

// PDF - 1
template <typename T>
void LinkList<T>::merge_lists(LinkList<T>& l1){
    Node<T> *h1 = l1.get_head()->next;
    Node<T> *h = this->head->next;
    this->size += l1.size;

    Node<T> *new_h = this->head;
    Node<T> *dummy = new_h;

    while(h && h1){
        if(h->data >= h1->data){
            new_h->next = h1;
            Node<T> *tmp = h1->next;
            h1->next = nullptr;
            new_h = new_h->next;
            h1 = tmp;
        }
        else{
            new_h->next = h;
            Node<T> *tmp = h->next;
            h->next = nullptr;
            new_h = new_h->next;
            h = tmp;
        }
    }

    if(h){
        new_h->next = h;
    }
    else if(h1){
        new_h->next = h1;
    }

    while(new_h){
        tail = new_h;
        new_h = new_h->next;
    }

    l1.get_head()->next = nullptr;
    this->head = dummy;

    h = dummy->next;
    h1 = h;
    if(!h)
        return;

    while(h->next){
        Node<T> *t = h->next->next;
        h->next->next = h1;
        h1 = h->next;
        h->next = t;
    }

    dummy->next = h1;
}

template <typename T>
Node<T>* LinkList<T>::reverse(Node<T>* head){
    if(!head || !head->next){
        return head;
    }
    Node<T> *ret = reverse(head->next);
    head->next->next = head;
    head->next = nullptr;
    return ret;
}

// 2.15
template <typename T>
void LinkList<T>::reverse_list(){
    Node<T>* t = reverse(head->next);
    head->next = t;
}

template <typename T>
void LinkList<T>::make_circular(const int& pos){
    if(pos >= size){
        std::cerr << "Invalid Operation" << endl;
        return;
    }
    Node<T> *p = head->next;

    int k = pos;
    while(k--){
        p = p->next;
    }
    tail->next = p;
}

template <typename T>
void LinkList<T>::dismake_circular(const int& pos){
    if(pos >= size){
        std::cerr << "Invalid Operation" << endl;
        return;
    }
    Node<T> *p = head->next;

    int k = pos;
    while(k--){
        p = p->next;
    }
    tail->next = nullptr;
}

// PDF - 2
template <typename T>
bool LinkList<T>::find_circle(){
    Node<T>* slow = head->next, *fast = head->next;
    while(fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            return true;
        }
    }
    return false;
}

// 2.13
template <typename T>
void LinkList<T>::delete_prev(const T& val){
    Node<T> *pre = head, *cur = head->next, *ppre = nullptr;
    if(!cur || !pre)
        return;
    while(cur){
        if(cur->data == val){
            break;
        }
        ppre = pre;
        pre = pre->next;
        cur = cur->next;
    }
    if(!ppre || !pre)
        return;
    ppre->next = cur;
    pre->next = nullptr;
    delete pre;
}


// exer 1
template <typename T>
void SingleLinkList<T>::switch_neighbors(){
    Node<T> *dummy = new Node<T>(-1);
    dummy->next = head;

    Node<T> *pre = dummy;
    if(!pre->next)
        return;

    while(pre->next && pre->next->next){
        Node<T> *cur = pre->next, *suc = cur->next, *pos = suc->next;

        pre->next = suc;
        suc->next = cur;
        cur->next = pos;
        pre = cur;
    }

    head = dummy->next;
    delete dummy;
}

template <typename T>
Node<T> *SingleLinkList<T>::reverse_int(Node<T> *start, Node<T> *end)
{
    Node<T> *pre = nullptr;
    Node<T> *cur = head;
    Node<T> *nxt = head;
    while(cur != end){
        nxt = cur->next;
        cur->next = pre;
        pre->next = nxt;
        pre = cur;
        cur = nxt;
    }
    return pre;
}

template <typename T>
void SingleLinkList<T>::reverse_k(const int& k){
    if(!head)
        return;
    Node<T> *dummy = new Node<T>(-1);
    dummy->next = head;
    Node<T> *start = head;

    Node<T> *temp = nullptr;
    Node<T>*pre = dummy;
    Node<T> *curr = head;

    int cnt = 0;
    while(start){
        start = start->next;
        ++cnt;
    }

    int need = cnt / k;
    for (int i = 0; i < need; ++i){
        for (int j = 0; j < k - 1; ++j){
            temp = curr->next;
            curr->next = temp->next;
            temp->next = pre->next;
            pre->next = temp;
        }
        pre = curr;
        curr = pre->next;
    }

    head = dummy->next;
    delete dummy;
}

int main(){
    SingleLinkList<int> ll({1, 2, 3, 4, 5, 6});
    // ll.switch_neighbors();
    ll.reverse_k(4);
    ll.traverse();
    return 0;
}