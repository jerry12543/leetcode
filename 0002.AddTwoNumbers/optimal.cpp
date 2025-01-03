#include <algorithm>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode()
        : val(0)
        , next(nullptr) {}
    ListNode(int x)
        : val(x)
        , next(nullptr) {}
    ListNode(int x, ListNode* next)
        : val(x)
        , next(next) {}
};


class Solution {
public:
    static auto addTwoNumbers(ListNode* l1, ListNode* l2) -> ListNode* {
        // make sure l1 is longer than l2
        for (ListNode *l1ptr = l1, *l2ptr = l2; l2ptr; l1ptr = l1ptr->next, l2ptr = l2ptr->next) {
            if (!l1ptr) {
                swap(l1, l2);
                break;
            }
        }

        int carry = 0;
        auto* head = l1;
        ListNode* prev = nullptr;

        for (; l1; l1 = l1->next, l2 = (!l2) ? l2 : l2->next) {
            int const l1val = l1->val;
            int const l2val = !l2 ? 0 : l2->val;
            int const val = l1val + l2val + carry;
            carry = (val >= 10) ? 1 : 0;

            l1->val = val % 10;
            prev = l1;
        }
        if (carry != 0) {
            prev->next = new ListNode(carry);
        }
        return head;
    }
};