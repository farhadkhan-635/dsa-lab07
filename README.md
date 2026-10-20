# DSA Lab 07: Queues, Circular Queues and Deques

Data Structures and Algorithms, Department of Computing

| | |
|---|---|
| Name | Farhad Khan |
| CMS ID | 549034 |
| Class | BSCS-15E |
| Instructor | Sara Tariq Sheikh |
| Lab Engineer | Hassan Mohtashim |
| Lab Date | 20 October 2026 |

## About

This lab implements queues in C++ with arrays and linked nodes, a circular queue, and deques. Each structure is a class with private data and public functions. No vectors, `std::list`, `std::queue` or `std::deque` are used, and every operation is written by hand. Each task is one standalone source file that compiles and runs on its own.

## Files

| Name | Task | What it does |
|---|---|---|
| q1 | Linear queue using an array | `ArrayQueue` with capacity 5. Full when `rear == 4`, so insertion is rejected even when earlier places are free. Both indices reset to -1 when the last value is removed, which makes the queue usable again. |
| q2 | Queue using linked nodes | `LinkedQueue` with `front` and `rear` pointers. Enqueue and dequeue need no traversal. `rear` is reset when the last node is deleted, and `ClearQueue()` runs before exit. |
| q3 | Circular queue | `CircularQueue` with circular indexing, so freed places are reused without shifting. Full condition is `(rear + 1) % 5 == front`. Shows `front = 2` and `rear = 1` after the wraparound test. |
| q4 | Rotating service turns | Reuses the circular queue. `RotateTurn()` saves the front ID, removes it and enqueues it at the rear. Tested with an empty queue, one student, three students for five turns, and a full queue. |
| q5 | Deque using a circular array | `ArrayDeque` with `InsertFront`, `InsertRear`, `DeleteFront` and `DeleteRear`. Moving backward uses `(index + 5 - 1) % 5`. Tested with the only value deleted from each end. |
| q6 | Deque using linked nodes | `LinkedDeque` with doubly linked nodes and a repeating menu. No traversal for any insertion or deletion, `ClearDeque()` runs before exit, and invalid choices and empty-deque operations are handled. |

Each one is a single source file (q1 is `q1.cpp`, q2 is `q2.cpp`, and so on).

## How to run

Each file is a complete program on its own, so run them one at a time.

**Using an IDE (easiest)**

1. Open the file, for example `q1.cpp`, in your IDE.
2. Press the compile and run button.
   - Dev-C++: F11
   - Code::Blocks: F9
   - Visual Studio: Ctrl + F5
   - VS Code with a C++ extension: the play button at the top right
3. A console window opens. q1 to q5 run their tests on their own, and q6 shows a menu.

**Using the terminal (optional)**

If you have the g++ compiler installed, open a terminal in this folder and run:

```
g++ q1.cpp -o q1
./q1
```

The first line turns the source code into a program, and the second line runs it. On Windows use `.\q1` for the second line. For the other tasks replace q1 with q2, q3 and so on.

## Sample output

q3, wraparound in the circular queue:

```
10 dequeued
20 dequeued
60 enqueued
70 enqueued
Queue (front to rear): 30 40 50 60 70
front = 2, rear = 1
Queue is full, cannot enqueue 80
```

q4, rotating turns (students 101, 102, 103):

```
Turn 1:
Served student: 101
Queue (front to rear): 102 103 101
Turn 2:
Served student: 102
Queue (front to rear): 103 101 102
```

q5, circular array deque:

```
Deque (front to rear): 10 20 30
Deque (front to rear): 20
Deque (front to rear): 1 5 20 30 40
Deque is full, cannot insert 99 at the front
```

## Memory safety

- In q2 and q6 every node is allocated with `new` and released with `delete`.
- The front pointer is moved first and the node is deleted afterwards, so the rest of the structure is never lost.
- When the last node is removed, both `front` and `rear` are reset to `nullptr`. Without this, `rear` would point at freed memory and the next insertion would write into it.
- In q6 the links on both sides are repaired after every deletion, so `front->prev` and `rear->next` stay `nullptr` in a non-empty deque.
- `ClearQueue()` and `ClearDeque()` release the remaining nodes before the program ends.
- Objects that own nodes are never copied.
- Every array index is checked before use, so there is no access outside the arrays.
- All six programs were built with AddressSanitizer and UndefinedBehaviorSanitizer and ran with no errors or leaks. The queue and deque classes were also compared against a reference model over thousands of random operations.

## Concepts covered

- **FIFO:** the first value enqueued is the first one dequeued, like people waiting in a line.
- **Linear queue limitation:** dequeuing moves `front` forward but `rear` stays at the end. Once `rear == 4` insertion is rejected even if earlier places are free, and they come back into use only after the queue becomes empty and both indices reset.
- **Circular queue:** indices advance with `(index + 1) % 5`, so after the last place they return to place 0 and freed places are reused without shifting. Full means `(rear + 1) % 5 == front`, and empty means `front == -1`.
- **Printing a circular queue:** a plain loop from `front` to `rear` fails when `rear` is smaller than `front`, so display steps with the circular formula and stops after printing the `rear` value, which prints each value exactly once.
- **Deque vs queue:** a queue inserts only at the rear and removes only from the front. A deque allows insertion and deletion at both ends, so it can act as a queue or a stack.
- **Why the linked deque is doubly linked:** deleting at the rear needs the node before `rear`. With only `next` links it takes a walk through the list, while the `prev` link gives it in one step, so all four operations are O(1).

## Reference

Goodrich, M. T., Tamassia, R., & Mount, D. M. (2011). *Data Structures and Algorithms in C++* (2nd ed.). Wiley.
