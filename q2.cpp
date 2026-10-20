// Name    : Farhad Khan
// Reg No  : 549034
// Section : BSCS-15E
// Lab 07, Task 2: Implementing a queue using linked nodes

#include <iostream>
using namespace std;

class LinkedQueue
{
private:
    struct node
    {
        int data;
        node* next;   // the node behind this one, nullptr for the last node
    };
    node* front;      // first node, the next one to be removed, nullptr means empty
    node* rear;       // last node, where new values are added

public:
    LinkedQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    bool IsEmpty()
    {
        return front == nullptr;
    }

    // adds a value at the rear. Because rear is always kept, we never
    // have to walk through the list to find the end.
    void Enqueue(int value)
    {
        node* newNode = new node;
        newNode->data = value;
        newNode->next = nullptr;   // it will be the last node

        if (IsEmpty())
        {
            front = newNode;       // first node, it is both front and rear
        }
        else
        {
            rear->next = newNode;  // old last node now points to the new one
        }
        rear = newNode;
        cout << value << " enqueued" << endl;
    }

    // removes the node at the front, again no walking is needed
    void Dequeue()
    {
        if (IsEmpty())
        {
            cout << "Queue is empty, nothing to dequeue" << endl;
            return;
        }

        node* temp = front;       // remember the node we are removing
        cout << temp->data << " dequeued" << endl;
        front = front->next;      // move front first, so the rest is not lost

        if (front == nullptr)
        {
            // the last node was removed. rear still holds the address of
            // that node, so it must be reset too, otherwise the next
            // Enqueue would write through rear into freed memory.
            rear = nullptr;
        }

        delete temp;              // now the removed node can be released
    }

    // shows the front value but leaves it in the queue
    void Peek()
    {
        if (IsEmpty())
        {
            cout << "Queue is empty, nothing to peek" << endl;
            return;
        }

        cout << "Front value: " << front->data << endl;
    }

    // prints from front to rear
    void Display()
    {
        if (IsEmpty())
        {
            cout << "The queue is empty." << endl;
            return;
        }

        cout << "Queue (front to rear): ";
        node* curr = front;
        while (curr != nullptr)
        {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    // releases every node that is still in the queue
    void ClearQueue()
    {
        node* curr = front;
        while (curr != nullptr)
        {
            node* nextNode = curr->next;   // save it first, we cannot read next after delete
            delete curr;
            curr = nextNode;
        }
        front = nullptr;   // otherwise both pointers would keep pointing at freed memory
        rear = nullptr;
    }
};

int main()
{
    LinkedQueue q;

    cout << "Test 1: operations on an empty queue" << endl;
    q.Dequeue();
    q.Peek();
    q.Display();
    cout << "Is empty: " << (q.IsEmpty() ? "yes" : "no") << endl;

    cout << endl << "Test 2: enqueue 10 20 30, dequeue once, display and peek" << endl;
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    q.Dequeue();   // 10 leaves first, first in is first out
    q.Display();   // expected 20 30
    q.Peek();      // expected 20

    cout << endl << "Test 3: remove everything, including the only node" << endl;
    q.Dequeue();   // 20
    q.Display();   // only 30 is left
    q.Dequeue();   // 30, the only node, front and rear both reset
    q.Display();   // expected empty
    cout << "Is empty: " << (q.IsEmpty() ? "yes" : "no") << endl;
    q.Dequeue();   // one more on the empty queue

    cout << endl << "Test 4: insertion after the queue became empty" << endl;
    q.Enqueue(40);
    q.Display();
    q.Peek();

    cout << endl << "Test 5: leave some nodes and release them before exit" << endl;
    q.Enqueue(50);
    q.Enqueue(60);
    q.Display();
    q.ClearQueue();
    q.Display();   // must be empty, all nodes were released

    return 0;
}
