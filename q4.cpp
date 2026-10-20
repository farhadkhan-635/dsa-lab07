// Name    : Farhad Khan
// Reg No  : 549034
// Section : BSCS-15E
// Lab 07, Task 4: Rotating service turns using a circular queue

#include <iostream>
using namespace std;

const int SIZE = 5;   // the queue can hold at most 5 students

// same CircularQueue as Task 3, with Count() and RotateTurn() added at the end
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
            front = 0;
            rear = 0;
        }
        else
        {
            rear = (rear + 1) % SIZE;
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
            front = -1;
            rear = -1;
        }
        else
        {
            front = (front + 1) % SIZE;
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

    // prints from front to rear, each stored value exactly once
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

    void ShowIndices()
    {
        cout << "front = " << front << ", rear = " << rear << endl;
    }

    // number of values in the queue. With wraparound rear can be smaller than
    // front, adding SIZE before the % keeps the difference from going negative.
    int Count()
    {
        if (IsEmpty())
        {
            return 0;
        }
        return (rear - front + SIZE) % SIZE + 1;
    }

    // gives the student at the front their turn, then sends them to the back.
    // Only queue operations are used, no element is shifted by hand.
    void RotateTurn()
    {
        if (IsEmpty())
        {
            cout << "No students in the queue, nothing to rotate." << endl;
            return;
        }

        int served = items[front];   // save the front id before it is removed
        Dequeue();                   // remove it from the front
        Enqueue(served);             // and put the same id at the rear
                                     // (this cannot fail, Dequeue just freed a place)
        cout << "Served student: " << served << endl;
    }
};

// shows the queue and how many students are in it
// the queue is passed by reference so it is never copied
void ShowQueue(CircularQueue& q)
{
    q.Display();
    cout << "Students in queue: " << q.Count() << endl;
}

int main()
{
    cout << "Test 1: rotate an empty queue" << endl;
    CircularQueue a;
    a.RotateTurn();
    ShowQueue(a);

    cout << endl << "Test 2: rotate a queue with one student" << endl;
    CircularQueue b;
    b.Enqueue(201);
    b.RotateTurn();   // the only student is removed and added again
    ShowQueue(b);     // 201 must still be in the queue

    cout << endl << "Test 3: students 101 102 103, five turns" << endl;
    CircularQueue c;
    c.Enqueue(101);
    c.Enqueue(102);
    c.Enqueue(103);
    ShowQueue(c);
    for (int turn = 1; turn <= 5; turn++)
    {
        cout << endl << "Turn " << turn << ":" << endl;
        c.RotateTurn();
        ShowQueue(c);   // turn 1: 102 103 101, turn 2: 103 101 102
        c.ShowIndices();   // front and rear move forward and wrap past the last place
    }

    cout << endl << "Test 4: a completely full queue can still rotate" << endl;
    CircularQueue d;
    for (int id = 301; id <= 305; id++)
    {
        d.Enqueue(id);
    }
    d.RotateTurn();   // Dequeue frees one place and the same id takes it
    ShowQueue(d);     // expected 302 303 304 305 301

    return 0;
}
