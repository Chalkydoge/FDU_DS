#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <cstring>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::initializer_list;
using std::istringstream;
using std::string;
using std::vector;

template <typename T>
class SingleLinkList;

template <typename T>
class Node{
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
        SingleLinkList(const initializer_list<T>& ll);
        void convert2circular();
        void traverse();
        void dis_circular() {
            if(tail)
                tail->next = nullptr;
            return;
        }
        bool find_type(const T& val);
        bool add_type(const T& val);
        bool remove(const T &val);

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

template<typename T>
bool SingleLinkList<T>::add_type(const T& val){
    Node<T> *new_node = new Node<T>(val);
    ++size;
    if(size == 1){
        head = new_node;
        tail = new_node;
        return true;
    }
    else{
        tail->next = new_node;
        tail = tail->next;
        return true;
    }
    return false;
}

template<typename T>
bool SingleLinkList<T>::find_type(const T& val){
    if(!head){
        return false;
    }
    Node<T> *h = head;
    while(h){
        if(h->data == val){
            return true;
        }
        h = h->next;
    }
    return false;
}

template<typename T>
bool SingleLinkList<T>::remove(const T& val){
    if(!head){
        return false;
    }
    Node<T> *h = head, *pre = nullptr;
    while(h && size){
        if(h->data == val){
            if(h == head){
                h = head->next;
                Node<T> *tmp = head;
                delete tmp;
                head = h;
            }
            else{
                pre->next = h->next;
                Node<T> *tmp = h;
                delete tmp;
                h = pre->next;
            }
            --size;
            continue;
        }
        else{
            pre = h;
            h = h->next;
        }
    }
    if(pre)
        return true;
    else
        return false;
}

int main(){
    cout << "Please input your type!!!" << endl;
    string type = "";
    getline(cin, type);

    if(type == "int"){
        SingleLinkList<int> lll;
        string str;

        while(getline(cin, str)){
            string op1 = "", op2 = "";
            istringstream is(str);
            is >> op1 >> op2;
            if(op2.empty()){
                if(op1 == "printlist"){
                    lll.traverse();
                }
                else{
                    cerr << "Error" << endl;
                }
            }
            else{
                if(op1 == "add"){
                    cout << std::boolalpha << lll.add_type(stoi(op2)) << endl;
                }
                else if(op1 == "remove"){
                    cout << std::boolalpha << lll.remove(stoi(op2)) << endl;
                }
                else if(op1 == "find"){
                    cout << std::boolalpha << lll.find_type(stoi(op2)) << endl;
                }
                else{
                    cerr << "Error" << endl;
                }
            }
        }
    }
    else if(type == "double" || type == "float"){
        SingleLinkList<double> lll;
        string str;
        while(getline(cin, str)){
            string op1 = "", op2 = "";
            istringstream is(str);
            is >> op1 >> op2;
            if(op2.empty()){
                if(op1 == "printlist"){
                    lll.traverse();
                }
                else{
                    cerr << "Error" << endl;
                }
            }
            else{
                if(op1 == "add"){
                    cout << std::boolalpha << lll.add_type(stod(op2)) << endl;
                }
                else if(op1 == "remove"){
                    cout << std::boolalpha << lll.remove(stod(op2)) << endl;
                }
                else if(op1 == "find"){
                    cout << std::boolalpha << lll.find_type(stod(op2)) << endl;
                }
                else{
                    cerr << "Error" << endl;
                }
            }
        }
    }
    else if(type == "string" || type == "char"){
        SingleLinkList<string> lll;
        string str;

        while(getline(cin, str)){
            string op1 = "", op2 = "";
            istringstream is(str);
            is >> op1 >> op2;
            if(op2.empty()){
                if(op1 == "printlist"){
                    lll.traverse();
                }
                else{
                    cerr << "Error" << endl;
                }
            }
            else{
                if(op1 == "add"){
                    cout << std::boolalpha << lll.add_type(op2) << endl;
                }
                else if(op1 == "remove"){
                    cout << std::boolalpha << lll.remove(op2) << endl;
                }
                else if(op1 == "find"){
                    cout << std::boolalpha << lll.find_type(op2) << endl;
                }
                else{
                    cerr << "Error" << endl;
                }
            }
        }
    }
    else{
        cerr << "Invalid type!!!" << endl;
        return -1;
    }


    return 0;
}