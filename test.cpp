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

void testDoublyLinkedCircularList()
{
    DoublyLinkedCircularList<int> list;

    for (int i = 0; i < 10; i++)
        list.append(i);

    for (int i = 0; i > -10; i--)
        list.prepend(i);

    for (int i = 0; i < 3; i++)
        list.removeHead();

    for (int i = 0; i < 3; i++)
        list.removeTail();

    list.print();
    list.printReverse();
}

void linkedListTest2()
{
    DoublyLinkedCircularList<int> list;

    for (int i = 5; i < 10; i++)
    {
        list.append(i);
        list.print();
    }
}

void testStack()
{
    Stack<int> stack;

    for (int i = 0; i < 10; i++)
        stack.push(i);

    for (int i = 0; i < 3; i++)
        stack.pop();

    stack.print();
}

void testQueue()
{
    Queue<int> queue;

    for (int i = 0; i < 100; i++)
        queue.enqueue(i);

    for (int i = 0; i < 50; i++)
        cout << queue.dequeue() << ", ";
    cout << endl;

    queue.print();
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
    linkedListTest2();

    return 0;
}