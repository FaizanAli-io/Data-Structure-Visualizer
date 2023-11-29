#include "Dependencies/Structures.h"

void testDynamicSafeArray()
{
    DynamicSafeArray<int> arr;

    for (int i = 0; i < 20; i++)
        arr.append(i);

    for (int i = 11; i < 20; i++)
        arr.remove(i);

    arr.print();
}

void testStack()
{
    Stack<int> stack;

    for (int i = 0; i < 10; i++)
    {
        stack.push(i);
        stack.print();
    }

    for (int i = 0; i < 10; i++)
    {
        stack.pop();
        stack.print();
    }
}

void testQueue()
{
    Queue<int> queue;

    for (int i = 0; i < 10; i++)
    {
        queue.enqueue(i);
        queue.print();
    }

    for (int i = 0; i < 10; i++)
    {
        queue.dequeue();
        queue.print();
    }
}

void testAVLTree()
{
    AVLTree<int> tree;

    for (int i = 1; i < 16; i++)
        tree.insert(i);

    tree.remove(4);
    tree.remove(5);
    tree.remove(6);
    tree.remove(7);
    tree.remove(3);
    tree.remove(2);

    tree.inorder();
    tree.levelorder();
}

int main()
{
    testStack();
    cout << endl;

    testQueue();
    cout << endl;

    return 0;
}