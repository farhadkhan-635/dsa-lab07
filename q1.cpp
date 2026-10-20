// Name    : Farhad Khan
// Reg No  : 549034
// Section : BSCS-15E
// Lab 07, Task 1: Implementing a linear queue using an array

#include <iostream>
using namespace std;

const int SIZE = 5;   // the queue can hold at most 5 values

class ArrayQueue
{
private:
    int items[SIZE];   // storage for the queue
    int front;         // index of the first value, -1 means the queue is empty
    int rear;          // index of the last value, -1 means the queue is empty

public:
    ArrayQueue()
    {
        front = -1;
        rear = -1;
    }

    bool IsEmpty()
    {
        return front == -1;
    }

    // this is a linear queue, so once rear sits on the last index nothing
    // more can be inserted, even when front has moved ahead and the earlier
    // places are free. We do not shift items and we do not wrap around,
    // those places only come back into use after the queue becomes empty
    // and both indices reset to -1.
    bool IsFull()
    {
        return rear == SIZE - 1;
    }

    // inserts a value at the rear
    void Enqueue(int value)
    {
        if (IsFull())
        {
            cout << "Queue is full (rear is at the last place), cannot enqueue " << value << endl;
            return;
        }

        if (IsEmpty())
        {
            front = 0;   // very first value, both indices move to place 0
            rear = 0;
        }
        else
        {
            rear++;      // later values only move rear forward
        }

        items[rear] = value;
        cout << value << " enqueued" << endl;
    }

    // removes the value at the front and shows it
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
            // that was the last value, so the queue is empty again and
            // both indices go back to -1. This reset is what lets the
            // earlier places be used again.
            front = -1;
            rear = -1;
        }
        else
        {
            front++;   // the next value becomes the front, nothing is shifted
        }
    }

    // shows the front value but leaves it in the queue
    void Peek()
    {
        if (IsEmpty())
        {
            cout << "Queue is empty, nothing to peek" << endl;
            return;
        }

        cout << "Front value: " << items[front] << endl;
    }

    // prints from front to rear, so the oldest value comes first
    void Display()
    {
        if (IsEmpty())
        {
            cout << "The queue is empty." << endl;
            return;
        }

        cout << "Queue (front to rear): ";
        for (int i = front; i <= rear; i++)
        {
            cout << items[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    ArrayQueue q;

    cout << "Test 1: enqueue 10 20 30 40 50" << endl;
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    q.Enqueue(40);
    q.Enqueue(50);
    q.Display();
    cout << "Is full: " << (q.IsFull() ? "yes" : "no") << endl;

    cout << endl << "Test 2: dequeue twice, then try to enqueue 60" << endl;
    q.Dequeue();   // 10
    q.Dequeue();   // 20
    q.Enqueue(60); // rear is still 4, so this must be rejected
    q.Display();   // expected 30 40 50
    q.Peek();      // expected 30

    cout << endl << "Test 3: empty the queue, dequeue again, then enqueue 70" << endl;
    q.Dequeue();   // 30
    q.Dequeue();   // 40
    q.Dequeue();   // 50, last value so both indices reset
    q.Display();
    cout << "Is empty: " << (q.IsEmpty() ? "yes" : "no") << endl;
    q.Dequeue();   // dequeue on the empty queue
    q.Peek();      // peek on the empty queue
    q.Enqueue(70); // works again because of the reset
    q.Display();
    q.Peek();

    return 0;
}
