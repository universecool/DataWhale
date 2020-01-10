#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL){}
};

/* 1. 合并两个有序链表 */
//方法一：迭代
class Solution1_1
{
public:
    ListNode* MergeTwoLists(ListNode* l1, ListNode* l2)
    {
        if (l1 == NULL)
            return l2;
        if (l2 == NULL)
            return l1;

        ListNode* dummyHead = new ListNode(0);
        ListNode* p = l1, * q = l2, * curr = dummyHead;
        while (p != NULL && q != NULL)
        {
            if (p->val < q->val)
            {
                // curr->next = new ListNode(p->val);
                curr->next = p;
                p = p->next;
            }
            else
            {
                // curr->next = new ListNode(q->val);
                curr->next = q;
                q = q->next;
            }
            curr = curr->next;
        }
        if (p == NULL)
        {
            curr->next = q;
        }
        if (q == NULL)
        {
            curr->next = p;
        }
        // return dummyHead->next;
        //释放头结点
        ListNode* tmp = dummyHead;
        dummyHead = dummyHead->next;
        delete tmp;
        tmp = nullptr;
        return dummyHead;
    }
};
//方法二：递归
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == NULL)
            return l2;
        if (l2 == NULL)
            return l1;

        if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l2->next, l1);
            return l2;
        }
    }
};

/* 2. 删除链表的倒数第N个节点 */
class Solution2 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* first = dummyHead, * second = dummyHead;
        for (int i = 0; i <= n; i++) {
            first = first->next;
        }
        while (first != NULL) {
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        return dummyHead->next;
    }
};

/* 3. 旋转链表 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode *old_tail = head;
        int n;
        for (n = 1; old_tail->next != NULL; n++){
            old_tail = old_tail->next;
        }
        old_tail->next = head;
        ListNode *new_tail = head;
        for (int i=0; i < n - k % n - 1; i++){
            new_tail = new_tail->next;
        }
        head = new_tail->next;
        new_tail->next = NULL;
        return head;
    }
};