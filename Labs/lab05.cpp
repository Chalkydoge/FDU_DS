#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int a = -1) : val(a), next(nullptr){}
};

ListNode* build(vector<int>& nums){
    ListNode *head = new ListNode(nums[0]);
    ListNode *temp = head;
    size_t N = nums.size();
    for (size_t i = 1; i < N; ++i){
        temp->next = new ListNode(nums[i]);
        temp = temp->next;
    }
    return head;
}

void read_and_redup(ListNode* head){
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    while(head && head->next){
        if(head->val <= head->next->val){
            head = head->next;
        }
        else{
            ListNode *pre = dummy;
            while(pre->next->val < head->next->val){
                pre = pre->next;
            }
            ListNode *cur = head->next;
            head->next = cur->next;
            cur->next = pre->next;
            pre->next = cur;
        }
    }

    ListNode *tmp = dummy;
    ListNode *p1 = tmp->next;
    ListNode *p2 = p1->next;

    while(p1 && p2){
        if(p1->val != p2->val){
            tmp = tmp->next;
            p1 = p1->next;
            p2 = p2->next;
        }
        else{
            while(p2 && p2->val == p1->val){
                p2 = p2->next;
            }
            if(p2){
                tmp->next = p2;
                p1 = p2;
                p2 = p1->next;
            }
            else{
                tmp->next = nullptr;
                break;
            }
        }
    }

    tmp = dummy->next;
    while(tmp){
        cout << tmp->val;
        tmp = tmp->next;
    }
}

int longestPalindrome(const string& str){
    string tmp;
    for(char c:str){
        tmp += '$';
        tmp += c;
    }
    tmp += '$';

    int N = (int)tmp.size();
    int max_right = 0, max_len = 0;
    int center = 0, pos = 0;
    vector<int> p(N, 0);


    for (int i = 0; i < N; ++i){
        if(i < max_right){
            int mirror = 2 * center - i;
            p[i] = min(max_right - i, p[mirror]);
        }
        else{
            int left = i - p[i] - 1;
            int right = i + p[i] + 1;
            while(left >= 0 && right < N && tmp[left] == tmp[right]){
                --left;
                ++right;
                ++p[i];
            }
            if(i + p[i] > max_right){
                max_right = i + p[i];
                center = i;
            }
            if(p[i] > max_len){
                max_len = p[i];
                pos = (i - max_len) / 2;
            }
        }
    }

    cout << str.substr(pos, max_len) << endl;
    return max_len;
}

int main(){
    // int N;
    // vector<int> nums;

    // cin >> N;
    // while(N--){
    //     int tmp;
    //     cin >> tmp;
    //     nums.push_back(tmp);
    // }

    // ListNode *head = build(nums);
    // read_and_redup(head);

    int res = longestPalindrome("abababa");
    cout << res;
    return 0;
}
