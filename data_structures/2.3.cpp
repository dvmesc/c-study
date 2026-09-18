//
// Created by 0 on 2026/8/19.
//

#include <iostream>
#include <ostream>
using   namespace std;


struct Node {
    int value;
    Node* next;

    explicit  Node(int v): value(v) , next(nullptr) {}
};


class  CircularLinkedList {
public:
    Node* tail;

private:
    CircularLinkedList(): tail(nullptr) {}

    ~CircularLinkedList() {
        if (tail == nullptr) {
            return;
        }

        Node* head = tail->next;
        tail->next=nullptr;
        while (head != nullptr) {
            Node* next=head->next;
            delete head;
            head=next;
        }
    }

    void pushback(int value) {
        Node* temp = new Node(value);
        if (tail == nullptr) {
            tail=temp;
            tail->next=tail;
            return;
        }

        temp->next=tail->next;
        tail->next =temp;
        tail=temp;
    }

    void push_front(int value) {
        Node* temp = new Node(value);
        if (tail == nullptr) {
            tail=temp;
            tail->next=tail;
            return;
        }

        temp->next=tail->next;
        tail->next=temp;
    }


    bool removevalue(int value) {
        if (tail == nullptr) {
            return false;
        }

        Node* prev = tail;
        Node* cur = tail->next;
        do {
            if (cur->value == value) {
                if (cur == prev) {
                    delete cur;
                    tail=nullptr;
                    return true;
                }

                prev->next=cur->next;
                if (cur == tail) {
                    tail=prev;

                }
                delete cur;
                return true;

            }

            prev=cur;
            cur=cur->next;
        }while (cur != tail->next);
    }

    void print() const{
        if (tail == nullptr) {
            cout<<"Empty List"<<endl;
        }

        Node* prev = tail->next;
        Node* cur = prev;
        do {
            cout<<cur->value<<" ";
            cur=cur->next;
        } while (cur!=prev);
        cout<<endl;
    }
};

























































































