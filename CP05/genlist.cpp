#include <iostream>
using namespace std;

class GenList;

struct GenListNode{
    int mark;
    int utype;
    GenListNode *tlink;
    union{
        char list_name;
        char atom;
        GenListNode *hlink;
    } value;

    GenListNode(int tp, char info) : mark(0), utype(tp), tlink(NULL){
        if(utype == 0)
            value.list_name = info;
        else
            value.atom = info;
    }

    GenListNode(GenListNode* hp): mark(0), utype(2){
        value.hlink = hp;
    }

    char get_info(GenListNode *elem){
        return elem->utype == 0 ? elem->value.list_name : elem->value.atom;
    }

};

class GenList{
    private:
        GenListNode *first;
        GenListNode *last;
        void traverse(GenListNode *ls);

    public:
        GenList(const char &val){
            first = new GenListNode(0, val);
            last = first;
        }
        ~GenList(){}
        void traverse(){
            traverse(first);
        }

        void append(const char &c){
            GenListNode *xx = new GenListNode(1, c);
            last->tlink = xx;
            last = xx;
        }

        void append(GenListNode* c){
            if(c){
                if(c->utype == 0){
                    GenListNode *t = new GenListNode(c);
                    last->tlink = t;
                    last = t;
                }
                else{
                    c->mark = 0;
                    last->tlink = c;
                    last = c;
                }
            }
        }

        GenListNode* get_head() const{
            return first;
        }
};

void GenList::traverse(GenListNode* ls){
    if(ls){
        ls->mark = 1;
        if(ls->utype == 0){
            cout << ls->value.list_name << '(';
        }
        else if(ls->utype == 1){
            cout << ls->value.atom;
            if(ls->tlink)
                cout << ',';
        }
        else if(ls->utype == 2){
            if(ls->value.hlink->mark == 0)
                traverse(ls->value.hlink);
            else
                cout << ls->value.hlink->value.list_name;
            if(ls->tlink)
                cout << ',';
        }
        traverse(ls->tlink);
    }
    else{
        cout << ')';
    }
}


int main(){
    // char c = 'x';
    GenList g('x');
    g.append('y');
    g.append('z');

    GenList h('c');
    h.append('q');
    h.append('r');
    h.append(g.get_head());
    h.traverse();

    return 0;
}
