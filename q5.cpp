// Name    : Farhad Khan
// Reg No  : 549034
// Section : BSCS-15E
// Lab 07, Task 5: Implementing a deque using a circular array

#include <iostream>
using namespace std;

const int SIZE = 5;   // the deque can hold at most 5 values

// a deque is a queue that works at both ends: values can be inserted and
// deleted at the front and at the rear, so it can act like a queue or a stack
class ArrayDeque
{
private:
    int items[SIZE];   // storage for the deque
    int front;         // index of the first value, -1 means the deque is empty
    int rear;          // index of the last value, -1 means the deque is empty

public:
    ArrayDeque()
    {
        front = -1;
        rear = -1;
    }

    bool IsEmpty()
    {
        return front == -1;
    }

    bool IsFull()
    {
        return (rear + 1) % SIZE == front;
    }

    void InsertFront(int value)
    {
        if (IsFull())
        {
            cout << "Deque is full, cannot insert " << value << " at the front" << endl;
            return;
        }

        if (IsEmpty())
        {
            front = 0;   // first value, both indices move to place 0
            rear = 0;
        }
        else
        {
            // move front one step backward. SIZE is added before the % so that
            // going back from place 0 lands on the last place and not on -1.
            front = (front + SIZE - 1) % SIZE;
        }

        items[front] = value;
        cout << value << " inserted at the front" << endl;
    }

    void InsertRear(int value)
    {
        if (IsFull())
        {
            cout << "Deque is full, cannot insert " << value << " at the rear" << endl;
            return;
        }

        if (IsEmpty())
        {
            front = 0;
            rear = 0;
        }
        else
        {
            rear = (rear + 1) % SIZE;   // one step forward, wraps to 0 after the last place
        }

        items[rear] = value;
        cout << value << " inserted at the rear" << endl;
    }

    void DeleteFront()
    {
        if (IsEmpty())
        {
            cout << "Deque is empty, nothing to delete from the front" << endl;
            return;
        }

        cout << items[front] << " deleted from the front" << endl;

        if (front == rear)
        {
            front = -1;   // that was the only value, deque is empty again
            rear = -1;
        }
        else
        {
            front = (front + 1) % SIZE;
        }
    }

    void DeleteRear()
    {
        if (IsEmpty())
        {
            cout << "Deque is empty, nothing to delete from the rear" << endl;
            return;
        }

        cout << items[rear] << " deleted from the rear" << endl;

        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            rear = (rear + SIZE - 1) % SIZE;   // one step backward
        }
    }

    // prints from front to rear, each stored value exactly once.
    // we stop right after printing the rear value, so this also works when
    // rear is smaller than front or when the deque is full.
    void Display()
    {
        if (IsEmpty())
        {
            cout << "The deque is empty." << endl;
            return;
        }

        cout << "Deque (front to rear): ";
        int i = front;
        while (true)
        {
            cout << items[i] << " ";
            if (i == rear)
            {
                break;
            }
            i = (i + 1) % SIZE;
        }
        cout << endl;
    }
};

int main()
{
    ArrayDeque d;

    cout << "Test 1: from empty, insert 20 at rear, 10 at front, 30 at rear" << endl;
    d.InsertRear(20);
    d.InsertFront(10);
    d.InsertRear(30);
    d.Display();   // expected 10 20 30

    cout << endl << "Test 2: delete from rear, then from front" << endl;
    d.DeleteRear();    // 30
    d.DeleteFront();   // 10
    d.Display();       // expected 20

    cout << endl << "Test 3: insert 5 at front, 30 and 40 at rear, then 1 at front" << endl;
    d.InsertFront(5);
    d.InsertRear(30);
    d.InsertRear(40);
    d.InsertFront(1);
    d.Display();       // expected 1 5 20 30 40
    cout << "Is full: " << (d.IsFull() ? "yes" : "no") << endl;

    cout << endl << "Test 4: further insertion at either end must be rejected" << endl;
    d.InsertFront(99);
    d.InsertRear(99);
    d.Display();       // deque must not change

    cout << endl << "Test 5: only value, deleted from the front, then from empty" << endl;
    ArrayDeque e;
    e.InsertRear(7);
    e.DeleteFront();   // the only value leaves from the front
    e.Display();
    e.DeleteFront();   // deletion from the empty deque
    e.DeleteRear();    // from the other end too

    cout << endl << "Test 6: only value, deleted from the rear, then from empty" << endl;
    ArrayDeque f;
    f.InsertFront(8);
    f.DeleteRear();    // the only value leaves from the rear
    f.Display();
    f.DeleteRear();    // deletion from the empty deque
    f.DeleteFront();   // from the other end too
    f.InsertFront(9);  // works again after the reset
    f.Display();

    return 0;
}
