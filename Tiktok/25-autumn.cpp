/*
字节 - 25届秋招一面
链表判断是否有环，如果有环，返回环的入口。
OJ:https://leetcode.cn/problems/linked-list-cycle-ii/description/
*/
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *detectCycle(ListNode *head) {
    ListNode *slow = head,*fast = head;
    while(fast != NULL)
    {
        if(slow -> next == NULL || fast -> next == NULL || fast -> next -> next == NULL)
        {
            return NULL;
        }
        slow = slow -> next;
        fast = fast -> next -> next;
        if(slow == fast)
        {
            break;
        }
    }
    ListNode *med = head;
    while(med != slow)
    {
        med = med -> next;
        slow = slow -> next;
    }
    return med;
}

int main()
{
    ListNode *head = new ListNode(3);
    head -> next = new ListNode(2);
    head -> next -> next = new ListNode(0);
    head -> next -> next -> next = new ListNode(-4);
    head -> next -> next -> next -> next = head -> next;
    cout << detectCycle(head) -> val << endl;
    return 0;
}