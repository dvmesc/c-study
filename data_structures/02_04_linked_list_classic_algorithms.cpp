#include <iostream>
#include <vector>

using namespace std;

// 链表节点：只保存当前值和后继指针。
struct Node {
    int val;
    Node* next;

    explicit Node(int value) : val(value), next(nullptr) {}
};

// 尾插法建表：便于快速构造测试数据。
Node* buildList(const vector<int>& values) {
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int value : values) {
        Node* node = new Node(value);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

// 打印普通单链表。这里默认链表无环。
void printList(Node* head) {
    Node* cur = head;
    while (cur != nullptr) {
        cout << cur->val << ' ';
        cur = cur->next;
    }
    cout << '\n';
}

// 释放无环链表的所有节点。
void destroyList(Node* head) {
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

// 获取第 index 个节点，便于构造测试场景。
Node* getNodeAt(Node* head, int index) {
    Node* cur = head;
    while (cur != nullptr && index > 0) {
        cur = cur->next;
        --index;
    }
    return cur;
}

// 获取链表尾结点。
Node* getTail(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }

    Node* cur = head;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}

// 1. 找中间结点：
// 慢指针每次走 1 步，快指针每次走 2 步。
// 当快指针走到末尾时，慢指针正好走到中间。
// 若长度为偶数，这里返回“靠后”的那个中间结点。
Node* findMiddle(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }

    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 2. 找倒数第 k 个结点：
// 先让 fast 走 k 步，拉开距离。
// 然后 fast 和 slow 一起走，直到 fast 走到空。
// 此时 slow 恰好停在倒数第 k 个结点。
Node* findKthFromEnd(Node* head, int k) {
    if (head == nullptr || k <= 0) {
        return nullptr;
    }

    Node* fast = head;
    for (int i = 0; i < k; ++i) {
        if (fast == nullptr) {
            return nullptr;
        }
        fast = fast->next;
    }

    Node* slow = head;
    while (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// 3. 判断链表是否有环：
// 若存在环，快慢指针最终一定会在环内相遇。
bool hasCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

// 4. 找环的入口：
// 第一步：先用快慢指针在环内相遇。
// 第二步：一个指针回到头结点，另一个留在相遇点。
// 两个指针都改成每次走 1 步，再次相遇的位置就是环入口。
Node* detectCycleEntry(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            Node* ptr1 = head;
            Node* ptr2 = slow;
            while (ptr1 != ptr2) {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }
            return ptr1;
        }
    }
    return nullptr;
}

// 5. 合并两个有序链表：
// 使用带头结点的 dummy，可以统一处理“新链表第一个结点”的连接逻辑。
// 每次从两个链表头部选更小的那个接到结果链表后面。
Node* mergeSortedLists(Node* head1, Node* head2) {
    Node dummy(0);
    Node* tail = &dummy;

    while (head1 != nullptr && head2 != nullptr) {
        if (head1->val <= head2->val) {
            tail->next = head1;
            head1 = head1->next;
        } else {
            tail->next = head2;
            head2 = head2->next;
        }
        tail = tail->next;
    }

    if (head1 != nullptr) {
        tail->next = head1;
    } else {
        tail->next = head2;
    }

    return dummy.next;
}

int main() {
    cout << "=== 1. 找中间结点 ===\n";
    Node* list1 = buildList({1, 2, 3, 4, 5, 6});
    printList(list1);
    Node* middle = findMiddle(list1);
    if (middle != nullptr) {
        cout << "中间结点(偶数长度取靠后者): " << middle->val << "\n\n";
    }
    destroyList(list1);

    cout << "=== 2. 找倒数第 k 个结点 ===\n";
    Node* list2 = buildList({10, 20, 30, 40, 50});
    printList(list2);
    Node* kth = findKthFromEnd(list2, 2);
    if (kth != nullptr) {
        cout << "倒数第 2 个结点: " << kth->val << "\n\n";
    }
    destroyList(list2);

    cout << "=== 3. 判断有环并找入口 ===\n";
    Node* cycleList = buildList({1, 2, 3, 4, 5});
    Node* entry = getNodeAt(cycleList, 2);
    Node* cycleTail = getTail(cycleList);
    cycleTail->next = entry;
    cout << "是否有环: " << hasCycle(cycleList) << '\n';
    Node* cycleEntry = detectCycleEntry(cycleList);
    if (cycleEntry != nullptr) {
        cout << "环入口结点: " << cycleEntry->val << "\n\n";
    }
    cycleTail->next = nullptr;
    destroyList(cycleList);

    cout << "=== 4. 合并两个有序链表 ===\n";
    Node* a = buildList({1, 3, 5, 7});
    Node* b = buildList({2, 4, 6, 8});
    cout << "链表 A: ";
    printList(a);
    cout << "链表 B: ";
    printList(b);
    Node* merged = mergeSortedLists(a, b);
    cout << "合并结果: ";
    printList(merged);
    destroyList(merged);

    return 0;
}
