#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
struct ListNode
{
    T data;
    ListNode<T> *next;
    ListNode<T> *prev;

    ListNode(T data, ListNode<T> *next = nullptr, ListNode<T> *prev = nullptr)
        : data(data), next(next), prev(prev) {}
};

template <typename T>
struct TreeNode
{
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode(T data, TreeNode<T> *left = nullptr, TreeNode<T> *right = nullptr)
        : data(data), left(left), right(right) {}
};

template <typename T>
class DynamicSafeArray
{
    int size;
    T *data;

public:
    DynamicSafeArray() : size(0), data(nullptr) {}

    T &operator[](int index)
    {
        if (index >= size || index < 0)
            cout << "Invalid Index...\n";
        else
            return data[index];
    }

    void append(T val)
    {
        size++;
        T *newdata = new T[size];

        for (int i = 0; i < size - 1; i++)
            newdata[i] = data[i];
        newdata[size - 1] = val;

        delete[] data;
        data = newdata;
    }

    void remove(T val)
    {
        int ind = -1;
        for (int i = 0; i < size; i++)
            if (data[i] == val)
                ind = i;

        if (ind == -1)
            return;

        size--;
        T *newdata = new T[size];

        for (int i = 0; i < ind; i++)
            newdata[i] = data[i];
        for (int i = ind + 1; i < size + 1; i++)
            newdata[i - 1] = data[i];

        delete[] data;
        data = newdata;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
            cout << data[i] << ' ';
        cout << endl;
    }
};

template <typename T>
class DoublyLinkedCircularList
{
    ListNode<T> *head;
    ListNode<T> *tail;

public:
    DoublyLinkedCircularList() : head(nullptr), tail(nullptr) {}

    inline bool isEmpty() { return !head && !tail; }

    ListNode<T> *getHead() { return head; }

    void append(T data)
    {
        ListNode<T> *newNode = new ListNode<T>(data, head, tail);

        if (isEmpty())
            head = newNode;
        else
            tail->next = newNode;
        tail = newNode;
    }

    void prepend(T data)
    {
        ListNode<T> *newNode = new ListNode<T>(data, head, tail);

        if (isEmpty())
            tail = newNode;
        else
            head->prev = newNode;
        head = newNode;
    }

    T removeHead()
    {
        if (!isEmpty())
        {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            T temp = head->data;
            head = head->next;
            return temp;
        }
        return T();
    }

    T removeTail()
    {
        if (!isEmpty())
        {
            tail->prev->next = tail->next;
            tail->next->prev = tail->prev;
            T temp = tail->data;
            tail = tail->prev;
            return temp;
        }
        return T();
    }

    int getLength()
    {
        int size = 0;
        if (!isEmpty())
        {
            ListNode<T> *cur = head;
            do
            {
                size++;
                cur = cur->next;
            } while (cur != head);
        }
        return size;
    }

    void print()
    {
        if (!isEmpty())
        {
            ListNode<T> *cur = head;
            do
            {
                cout << cur->data << " -> ";
                cur = cur->next;
            } while (cur != head);
            cout << "NULL" << endl;
        }
        else
            cout << "List is Empty...\n";
    }

    void printReverse()
    {
        if (!isEmpty())
        {
            ListNode<T> *cur = tail;
            do
            {
                cout << cur->data << " -> ";
                cur = cur->prev;
            } while (cur != tail);
            cout << "NULL" << endl;
        }
        else
            cout << "List is Empty...\n";
    }
};

template <typename T>
class Stack
{
    ListNode<T> *top;

public:
    Stack() : top(nullptr) {}

    inline bool isEmpty() { return top == nullptr; }

    void push(T data)
    {
        ListNode<T> *newNode = new ListNode<T>(data, top);
        top = newNode;
    }

    T pop()
    {
        if (!isEmpty())
        {
            T data = top->data;
            top = top->next;
            return data;
        }
        return T();
    }

    T peek()
    {
        if (!isEmpty())
            return top->data;
    }

    void print()
    {
        ListNode<T> *cur = top;
        while (cur != nullptr)
        {
            cout << cur->data << " -> ";
            cur = cur->next;
        }
        cout << "NULL" << endl;
    }
};

template <typename T>
class Queue
{
    ListNode<T> *front;
    ListNode<T> *rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    inline bool isEmpty() { return rear == nullptr; }

    void enqueue(T data)
    {
        ListNode<T> *newNode = new ListNode<T>(data);

        if (isEmpty())
            rear = newNode;
        else
            front->next = newNode;
        front = newNode;
    }

    T dequeue()
    {
        if (!isEmpty())
        {
            T data = rear->data;
            rear = rear->next;
            return data;
        }
        return T();
    }

    T peek()
    {
        if (!isEmpty())
            return rear->data;
    }

    void print()
    {
        ListNode<T> *cur = rear;
        while (cur != nullptr)
        {
            cout << cur->data << " -> ";
            cur = cur->next;
        }
        cout << "NULL" << endl;
    }
};

template <typename T>
struct AVLTree
{
    TreeNode<T> *root;

    inline int max(int a, int b) { return a > b ? a : b; }

    inline int getBalance(TreeNode<T> *node) { return getHeight(node->left) - getHeight(node->right); }

    int getHeight(TreeNode<T> *node) { return node ? max(getHeight(node->left), getHeight(node->right)) + 1 : -1; }

    TreeNode<T> *leftRotate(TreeNode<T> *x)
    {
        TreeNode<T> *y = x->right;
        TreeNode<T> *t = y->left;

        y->left = x;
        x->right = t;

        return y;
    }

    TreeNode<T> *rightRotate(TreeNode<T> *x)
    {
        TreeNode<T> *y = x->left;
        TreeNode<T> *t = y->right;

        y->right = x;
        x->left = t;

        return y;
    }

    TreeNode<T> *balanceTree(TreeNode<T> *node, T data)
    {
        int balance = getBalance(node);

        if (balance > 1)
        {
            if (data < node->left->data)
                node = rightRotate(node);

            else
            {
                node->left = leftRotate(node->left);
                node = rightRotate(node);
            }
        }

        else if (balance < -1)
        {
            if (data > node->right->data)
                node = leftRotate(node);
            else
            {
                node->right = rightRotate(node->right);
                node = leftRotate(node);
            }
        }

        return node;
    }

    TreeNode<T> *balanceTree(TreeNode<T> *node)
    {
        int balance = getBalance(node);

        if (balance > 1)
        {
            if (getBalance(node->left) >= 0)
                node = rightRotate(node);

            else
            {
                node->left = leftRotate(node->left);
                node = rightRotate(node);
            }
        }

        else if (balance < -1)
        {
            if (getBalance(node->right) <= 0)
                node = leftRotate(node);
            else
            {
                node->right = rightRotate(node->right);
                node = leftRotate(node);
            }
        }

        return node;
    }

    TreeNode<T> *insertHelper(TreeNode<T> *node, T data)
    {
        if (node == nullptr)
            return new TreeNode<T>(data);

        else if (data < node->data)
            node->left = insertHelper(node->left, data);
        else if (data > node->data)
            node->right = insertHelper(node->right, data);
        else
            return node;

        return balanceTree(node, data);
    }

    TreeNode<T> *nextNode(TreeNode<T> *node)
    {
        node = node->right;
        while (node->left)
            node = node->left;
        return node;
    }

    TreeNode<T> *lastNode(TreeNode<T> *node)
    {
        node = node->left;
        while (node->right)
            node = node->right;
        return node;
    }

    TreeNode<T> *removeHelper(TreeNode<T> *node, T data)
    {
        if (node == nullptr)
            return nullptr;
        else if (data < node->data)
            node->left = removeHelper(node->left, data);
        else if (data > node->data)
            node->right = removeHelper(node->right, data);

        else if (data == node->data)
        {
            if (!(node->left) && !(node->right))
                return nullptr;
            else if ((node->left) && !(node->right))
                node = node->left;
            else if (!(node->left) && (node->right))
                node = node->right;
            else if ((node->left) && (node->right))
            {
                T value = nextNode(node)->data;
                node->right = removeHelper(node->right, value);
                node->data = value;
            }
        }

        return balanceTree(node);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T data) { root = insertHelper(root, data); }

    void remove(T data) { root = removeHelper(root, data); }

    void inorder(TreeNode<T> *node = nullptr, int d = 0)
    {
        if (d == 0 && !node)
            node = root;

        if (node != nullptr)
        {
            inorder(node->left, d + 1);

            for (int i = 0; i < d; i++)
                cout << '\t';
            cout << node->data << endl;

            inorder(node->right, d + 1);
        }
    }

    void preorder(TreeNode<T> *node = nullptr, int d = 0)
    {
        if (d == 0 && !node)
            node = root;

        if (node != nullptr)
        {
            for (int i = 0; i < d; i++)
                cout << '\t';
            cout << node->data << endl;

            preorder(node->left, d + 1);

            preorder(node->right, d + 1);
        }
    }

    void postorder(TreeNode<T> *node = nullptr, int d = 0)
    {
        if (d == 0 && !node)
            node = root;

        if (node != nullptr)
        {
            postorder(node->left, d + 1);

            postorder(node->right, d + 1);

            for (int i = 0; i < d; i++)
                cout << '\t';
            cout << node->data << endl;
        }
    }

    void levelorder(TreeNode<T> *node = nullptr)
    {
        Queue<TreeNode<T> *> nodes;

        node ? nodes.enqueue(node) : nodes.enqueue(root);

        while (!nodes.isEmpty())
        {
            TreeNode<T> *current = nodes.dequeue();

            if (current->left)
                nodes.enqueue(current->left);
            if (current->right)
                nodes.enqueue(current->right);

            cout << current->data << ' ';
        }

        cout << endl;
    }
};
