#include <iostream>
#include <random>
#include <stack>
using std::cout;
using std::endl;
using std::stack;
using std::swap;

// 9.14
void BiBubbleSort(int arr[], int lo, int hi){
    bool flag = true;

    while(lo < hi){
        for (int i = hi; i > lo; --i){
            if(arr[i - 1] > arr[i]){
                swap(arr[i - 1], arr[i]);
                flag = false;
            }
        }

        if(flag)
            break;
        ++lo;

        for (int i = lo; i < hi; ++i){
            if(arr[i] > arr[i + 1]){
                swap(arr[i], arr[i + 1]);
            }
        }
        --hi;
    }
}

void print(int arr[], int lo, int hi){
    for (int i = lo; i <= hi; ++i){
        printf("%d ", arr[i]);
    }
}

// 9.16
int partition(int arr[], int lo, int hi){
    int tmp = lo + (rand() % (hi - lo + 1));
    swap(arr[lo], arr[tmp]);
    int pivot = arr[lo];
    int mi = lo;
    for (int k = lo + 1; k <= hi; ++k){
        if(arr[k] < pivot){
            swap(arr[++mi], arr[k]);
        }
    }
    swap(arr[lo], arr[mi]);
    return mi;
}

struct range{
    int begin;
    int end;
    range(int a, int b): begin(a), end(b){}
};

void QuickSort(int arr[], int lo, int hi){
    stack<range> stk;
    int n;
    do{
        while(hi - lo >= 2){
            n = partition(arr, lo, hi);
            // cout << lo << '\t' << n << '\t' << hi << endl;
            stk.push(range(n + 1, hi));
            hi = n;
        }

        if(stk.empty())
            break;

        lo = stk.top().begin;
        hi = stk.top().end;

        stk.pop();
    } while (1);
}

void QuickSort1(int arr[], int lo, int hi){
    if(hi - lo < 2)
        return;
    int mi = partition(arr, lo, hi);
    QuickSort1(arr, lo, mi);
    QuickSort1(arr, mi + 1, hi);
}

int main(){
    int arr[12] = {8, 6, 5, 1, 2, 3, 7, 9, 4, 0, 11, 10};
    // BiBubbleSort(arr, 0, 9);
    // QuickSort1(arr, 0, 9);
    QuickSort(arr, 0, 11);
    print(arr, 0, 11);
    return 0;
}
