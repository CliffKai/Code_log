/*
字节 - 秋招二面 2024/10/16
2. 32进制的两个链表加法（0 - 9，a - z）
给定两个 非空链表 l1和 l2 来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一个字符（0 - 9，a - z）。将这两数相加会返回一个新的链表。备注：a 代表 10， b 代表 11，以此类推
可以假设除了数字 0 之外，这两个数字都不会以零开头。
 示例 1：
第一个数：'1' -> 'a' -> 'z' （对应 1az）
第二个数：'2' -> 'b' -> 'y' （对应 2by）
相加得到：'3' -> 'n' -> '5'  (对应 3n5)

示例 2：
第一个数：          '9' -> '0' -> '1' （对应 901）
第二个数：'1' -> 'b' -> '3' -> '5' （对应 1b35）
相加得到：'1' -> 'k' -> '3' -> '6'  (对应 1k36)

//略有不同，但是思路是一样的
OJ:https://leetcode-cn.com/problems/add-two-numbers-ii/description/
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
//反转链表
ListNode* reverseList(ListNode* head) {
    if(head == nullptr)
    {
        return head;
    }
    ListNode *med1 = nullptr,*med2 = head,*med3 = head -> next;
    while(med3)
    {
        med2 -> next = med1;
        med1 = med2;
        med2 = med3;
        med3 = med3 -> next;
    }
    med2 -> next = med1;
    med1 = med2;
    return med1;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) {
        return l2;
    } else if (l2 == nullptr) {
        return l1;
    } else {
        l1 = reverseList(l1);
        l2 = reverseList(l2);
        ListNode* ans = new ListNode();
        ListNode* pre = ans;
        int sign = 0;
        pre->val = l1->val + l2->val;
        if (pre->val >= 10) {
            sign = 1;
            pre->val %= 10;
        }
        l1 = l1->next;
        l2 = l2->next;
        while (l1 != nullptr && l2 != nullptr) {
            pre->next = new ListNode((l1->val + l2->val) + sign);
            sign = 0;
            pre = pre->next;
            if (pre->val >= 10) {
                sign = 1;
                pre->val %= 10;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        if (l1 == nullptr && l2 == nullptr && sign == 1) {
            pre->next = new ListNode(sign);
            pre = pre->next;
        } else if (l2 == nullptr) {
            while (l1 != nullptr) {
                pre->next = new ListNode(l1->val + sign);
                sign = 0;
                pre = pre->next;
                if (pre->val >= 10) {
                    sign = 1;
                    pre->val %= 10;
                }
                l1 = l1->next;
            }
            if(sign)
            {
                pre->next = new ListNode(sign);
                pre = pre->next;
            }
        } else if (l1 == nullptr) {
            while (l2 != nullptr) {
                pre->next = new ListNode(l2->val + sign);
                sign = 0;
                pre = pre->next;
                if (pre->val >= 10) {
                    sign = 1;
                    pre->val %= 10;
                }
                l2 = l2->next;
            }
            if(sign)
            {
                pre->next = new ListNode(sign);
                pre = pre->next;
            }
        }
        return reverseList(ans);
    }
}

int main()
{
    //[1] + [9,9]
    ListNode *l1 = new ListNode(1);
    ListNode *l2 = new ListNode(9);
    l2 -> next = new ListNode(9);

    ListNode *ans = addTwoNumbers(l1,l2);
    while(ans != nullptr)
    {
        cout << ans -> val << " ";
        ans = ans -> next;
    }
    cout << endl;
    return 0;
}