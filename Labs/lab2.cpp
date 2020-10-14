#include <iostream>
#include <vector>
#include <queue>
using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::vector;

//### T1

struct Teams{
    int start_year;
    int power;
    int id;
    Teams(int a = 0, int b = 0, int c = 0): start_year(a), power(b), id(c){}
};


int main(){
    int N = 0, beg = 0, end = 0, period = 0;
    cin >> N >> period >> beg >> end;

    deque<int> dq;
    vector<Teams> vec(period - 1, Teams(beg, -1, -114514));
    // curr_que [x, x, x, x, ?]
    // cout << vec.size() << endl;
    vector<int> res;

    for (int i = 0; i < N; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        Teams tmp(a, b, c);
        if(!vec.empty() && vec.back().power >= tmp.power && vec.back().start_year == tmp.start_year){
            continue;
        }
        else{
            vec.push_back(tmp);
        }
    }

    for (int i = 0; i < period; ++i){
        vec.push_back(Teams(end, -1, -114514));
    }

    int j = 0;
    for(; j < period; ++j){
        while(!dq.empty() && vec[dq.back()].power < vec[j].power){
            dq.pop_back();
        }
        dq.push_back(j);
    }
    res.push_back(vec[dq.front()].id);

    N = vec.size();
    while(j < N - period){
        if(j - dq.front() >= period){
            dq.pop_front();
        }
        while(!dq.empty() && vec[dq.back()].power < vec[j].power){
            dq.pop_back();
        }
        dq.push_back(j);
        ++j;
        res.push_back(vec[dq.front()].id);
    }

    for (auto i : res){
        cout << i << endl;
    }
    return 0;
}