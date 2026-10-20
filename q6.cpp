// Name    : Farhad Khan
// Reg No  : 549034
// Section : BSCS-15E
// Lab 07, Task 6: Implementing a deque using linked nodes (menu driven)

// How a deque differs from a queue:
// a queue inserts only at the rear and removes only from the front (FIFO).
// A deque allows both insertion and deletion at either end, so it can work
// like a queue or like a stack.
//
// Why the nodes are doubly linked: DeleteRear needs the node just before rear.
// With only next links we would have to walk the whole list to find it. With
// a prev link it is one step back, so every operation at both ends is O(1).

#include <iostream>
using namespace std;

class LinkedDeque
{
private:
    struct node
    {
        int data;
        node* next;   // the node behind this one, nullptr for the last node
        node* prev;   // the node before this one, nullptr for the first node
    };
    node* front;      // first node, nullptr means the deque is empty
    node* rear;       // last node
                      // while the deque is not empty: front->prev and rear->next
                      // are always nullptr

public:
    LinkedDeque()
    {
        front = nullptr;
        rear = nullptr;
    }

    bool IsEmpty()
    {
        return front == nullptr;
    }

    // no walking is needed, front is already known
    void InsertFront(int value)
    {
        node* newNode = new node;
        newNode->data = value;
        newNode->prev = nullptr;    // it will be the first node
        newNode->next = front;      // the old first node goes behind it

        if (IsEmpty())
        {
            rear = newNode;         // only node, so it is the rear as well
        }
        else
        {
            front->prev = newNode;  // old first node points back to the new one
        }
        front = newNode;
        cout << value << " inserted at the front" << endl;
    }

    // no walking here either, rear is already known
    void InsertRear(int value)
    {
        node* newNode = new node;
        newNode->data = value;
        newNode->next = nullptr;    // it will be the last node
        newNode->prev = rear;       // the old last node goes before it

        if (IsEmpty())
        {
            front = newNode;        // only node, so it is the front as well
        }
        else
        {
            rear->next = newNode;   // old last node points forward to the new one
        }
        rear = newNode;
        cout << value << " inserted at the rear" << endl;
    }

    void DeleteFront()
    {
        if (IsEmpty())
        {
            cout << "Deque is empty, nothing to delete from the front" << endl;
            return;
        }

        node* temp = front;         // remember the node we are removing
        cout << temp->data << " deleted from the front" << endl;
        front = front->next;        // move front first, so the rest is not lost

        if (front == nullptr)
        {
            rear = nullptr;         // that was the only node, so rear must reset too
        }
        else
        {
            front->prev = nullptr;  // the new first node must not point back to the deleted one
        }

        delete temp;
    }

    void DeleteRear()
    {
        if (IsEmpty())
        {
            cout << "Deque is empty, nothing to delete from the rear" << endl;
            return;
        }

        node* temp = rear;
        cout << temp->data << " deleted from the rear" << endl;
        rear = rear->prev;          // the prev link gives the new last node in one step

        if (rear == nullptr)
        {
            front = nullptr;        // that was the only node, so front must reset too
        }
        else
        {
            rear->next = nullptr;   // the new last node must not point forward to the deleted one
        }

        delete temp;
    }

    // prints from front to rear
    void Display()
    {
        if (IsEmpty())
        {
            cout << "The deque is empty." << endl;
            return;
        }

        cout << "Deque (front to rear): ";
        node* curr = front;
        while (curr != nullptr)
        {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    // releases every node that is still in the deque
    void ClearDeque()
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
    LinkedDeque d;
    int choice = 0;
    int value;

    do
    {
        cout << endl;
        cout << "----- Linked Deque Menu -----" << endl;
        cout << "1. Insert at front" << endl;
        cout << "2. Insert at rear" << endl;
        cout << "3. Delete from front" << endl;
        cout << "4. Delete from rear" << endl;
        cout << "5. Display" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // if something that is not a number was typed, cin goes into a fail
        // state and the menu would loop forever, so reset it and drop that input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            d.InsertFront(value);
            break;
        case 2:
            cout << "Enter value: ";
            cin >> value;
            d.InsertRear(value);
            break;
        case 3:
            d.DeleteFront();
            break;
        case 4:
            d.DeleteRear();
            break;
        case 5:
            d.Display();
            break;
        case 6:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice, please enter a number from 1 to 6." << endl;
        }
    } while (choice != 6);

    // the user can exit while nodes are still in the deque, so release them here
    d.ClearDeque();
    return 0;
}
