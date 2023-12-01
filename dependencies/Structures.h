#include <iostream>
using namespace std;

#ifndef STRUCTURES
#define STRUCTURES

template <typename T>
struct DynamicSafeArray
{
    int size;
    T *data;

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
struct ListNode
{
    T data;
    ListNode<T> *next;

    ListNode(T data, ListNode<T> *next = nullptr)
        : data(data), next(next) {}
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
struct LinkedList
{
    ListNode<T> *head;
    ListNode<T> *tail;

    LinkedList() : head(nullptr), tail(nullptr) {}

    inline bool isEmpty() { return head == nullptr; }

    ListNode<T> *getHead() { return head; }

    ListNode<T> *getTail() { return tail; }

    void append(T data)
    {
        ListNode<T> *newNode = new ListNode<T>(data);

        if (isEmpty())
            head = newNode;
        else
            tail->next = newNode;
        tail = newNode;
    }

    void prepend(T data)
    {
        ListNode<T> *newNode = new ListNode<T>(data);

        if (isEmpty())
            tail = newNode;
        else
            newNode->next = head;
        head = newNode;
    }

    T removeHead()
    {
        if (isEmpty())
            return T();

        ListNode<T> *temp = head;

        if (temp == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
            head = head->next;

        T tempval = temp->data;
        delete temp;
        return tempval;
    }

    T removeTail()
    {
        if (isEmpty())
            return T();

        ListNode<T> *temp = head;

        if (temp == tail)
        {
            head = nullptr;
            tail = nullptr;
        }

        else
        {
            while (temp->next != tail)
                temp = temp->next;

            tail = temp;
            temp = tail->next;
            tail->next = nullptr;
        }

        T tempval = temp->data;
        delete temp;
        return tempval;
    }

    int getLength()
    {
        int size = 0;
        for (ListNode<T> *cur = head; cur != nullptr; cur = cur->next)
            size++;
        return size;
    }

    void print()
    {
        for (ListNode<T> *cur = head; cur != nullptr; cur = cur->next)
            cout << cur->data << " -> ";
        cout << "NULL" << endl;
    }

    ~LinkedList()
    {
        if (head != nullptr)
            delete head;
        if (tail != nullptr)
            delete tail;
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
        LinkedList<TreeNode<T> *> nodes;

        node ? nodes.append(node) : nodes.removeTail(root);

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

#endif
