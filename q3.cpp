// Name    : Farhad Khan
// Reg No  : 549034
// Section : BSCS-15E
// Lab 07, Task 3: Implementing a circular queue

#include <iostream>
using namespace std;

const int SIZE = 5;   // the queue can hold at most 5 values

class CircularQueue
{
private:
    int items[SIZE];   // storage for the queue
    int front;         // index of the first value, -1 means the queue is empty
    int rear;          // index of the last value, -1 means the queue is empty

public:
    CircularQueue()
    {
        front = -1;
        rear = -1;
    }

    bool IsEmpty()
    {
        return front == -1;
    }

    // full means the next place after rear is where front is sitting.
    // Because the indices wrap around, this works wherever front and rear are.
    // An empty queue is never reported full: front is -1, and (rear + 1) % SIZE
    // can never give -1.
    bool IsFull()
    {
        return (rear + 1) % SIZE == front;
    }

    void Enqueue(int value)
    {
        if (IsFull())
        {
            cout << "Queue is full, cannot enqueue " << value << endl;
            return;
        }

        if (IsEmpty())
        {
            front = 0;   // very first value, both indices move to place 0
            rear = 0;
        }
        else
        {
            rear = (rear + 1) % SIZE;   // after the last place it goes back to place 0
        }

        items[rear] = value;
        cout << value << " enqueued" << endl;
    }

    void Dequeue()
    {
        if (IsEmpty())
        {
            cout << "Queue is empty, nothing to dequeue" << endl;
            return;
        }

        cout << items[front] << " dequeued" << endl;

        if (front == rear)
        {
            front = -1;   // last value removed, queue is empty again
            rear = -1;
        }
        else
        {
            front = (front + 1) % SIZE;   // front can wrap around too
        }
    }

    void Peek()
    {
        if (IsEmpty())
        {
            cout << "Queue is empty, nothing to peek" << endl;
            return;
        }

        cout << "Front value: " << items[front] << endl;
    }

    // prints from front to rear, each stored value exactly once.
    // A normal for loop from front to rear would fail when rear is smaller
    // than front, so we step with the circular formula and stop right after
    // printing the rear value. This also works when the queue is completely full.
    void Display()
    {
        if (IsEmpty())
        {
            cout << "The queue is empty." << endl;
            return;
        }

        cout << "Queue (front to rear): ";
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

    // small helper so main can show where front and rear are
    void ShowIndices()
    {
        cout << "front = " << front << ", rear = " << rear << endl;
    }
};

int main()
{
    CircularQueue q;

    cout << "Test 1: enqueue 10 20 30 40 50" << endl;
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    q.Enqueue(40);
    q.Enqueue(50);
    q.Display();
    q.ShowIndices();   // front = 0, rear = 4
    cout << "Is full: " << (q.IsFull() ? "yes" : "no") << endl;

    cout << endl << "Test 2: dequeue twice, then enqueue 60 and 70 (wraparound)" << endl;
    q.Dequeue();   // 10
    q.Dequeue();   // 20
    q.Enqueue(60); // goes into place 0, which was freed earlier
    q.Enqueue(70); // goes into place 1
    q.Display();   // expected 30 40 50 60 70
    q.ShowIndices(); // expected front = 2, rear = 1
    cout << "Is full: " << (q.IsFull() ? "yes" : "no") << endl;

    cout << endl << "Test 3: another insertion must be rejected" << endl;
    q.Enqueue(80);
    q.Display();   // queue must not change
    q.Peek();      // expected 30

    cout << endl << "Test 4: empty the queue (rear is smaller than front on the way)" << endl;
    q.Dequeue();   // 30
    q.Display();   // 40 50 60 70, rear is 1 and front is 3
    q.ShowIndices();
    q.Dequeue();   // 40
    q.Dequeue();   // 50
    q.Dequeue();   // 60
    q.Dequeue();   // 70, last value so both indices reset
    q.Display();
    q.ShowIndices();
    q.Dequeue();   // one further dequeue on the empty queue
    q.Peek();      // peek on the empty queue

    cout << endl << "Test 5: insertion into the empty queue again" << endl;
    q.Enqueue(90);
    q.Display();
    q.ShowIndices();   // front = 0, rear = 0

    return 0;
}
