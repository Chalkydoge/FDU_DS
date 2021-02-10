#include <iostream>
#include <map>
#include <set>
using std::cout;
using std::endl;
using std::map;
using std::set;

struct node{
    int a;
    double b;
    node(int a = 0, double b = 3.0): a(a), b(b){}
    bool operator==(const node& o){
        return a == o.a && b == o.b;
    }
    bool friend operator<(const node& a, const node& b){
        if(a.a < b.a)
            return true;
        else if(a.a == b.a){
            return a.b < b.b;
        }
        else{
            return false;
        }
    }
};

struct node_cmp{
    bool operator()(const node& a, const node& b){
        if(a.a < b.a)
            return true;
        else if(a.a == b.a){
            return a.b < b.b;
        }
        else{
            return false;
        }
    }
};

map<int, set<node>> m;

int main(){
    m[0].emplace(0, 1.1);
    m[0].emplace();
    m[1].emplace(1, 2.2);
    m[2].insert(node(1, 2.77));
    m[2].insert(node(1, 2.77));
    for(auto& p: m){
        cout << p.first << endl;
        for(auto& i: p.second){
            cout << i.a << '\t' << i.b << endl;
        }
    }

    return 0;
}
