#include "FineGrainedQueue.h"

void FineGrainedQueue::push_back(int data)
{
    Node* node = new Node(data);
    if (head == nullptr)
    {
        head = node;
        return;
    }
    Node* last = head;
    while (last->next != nullptr)
    {
        last = last->next;
    }
    last->next = node;
    return;
}

void FineGrainedQueue::show()
{
    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
        std::cout << ptr->value << " ";
    }
    std::cout << endl;
}


void FineGrainedQueue::insertIntoMiddle(int value, int pos) {
    Node* cur;
    Node* newNode = new Node(value);
    queue_mutex->lock();
    cur = this->head;
    if (cur)
        cur->node_mutex->lock();
    queue_mutex->unlock();
    bool flag = 1;
    for (; pos > 0; --pos) {
        if (cur->next != nullptr) {
            Node* next = cur->next;
            next->node_mutex->lock(); 
            cur->node_mutex->unlock(); 
            cur = next;
        }
        else {
            flag = 0;
            break;
        }
    }
    if (flag) { //Insert in the middle of list
        swap(cur->value, newNode->value);
        Node* next = cur->next;
        cur->next = newNode;
        newNode->next = next;
        cur->node_mutex->unlock();
    }
    else { //Insert in the end of list
        cur->next = newNode;
        cur->node_mutex->unlock();
    }
}
